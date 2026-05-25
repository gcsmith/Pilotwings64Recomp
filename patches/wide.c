#include "patches.h"
#include "uv_geometry.h"
#include "uv_graphics.h"

// gGfxView* are the scene view bounds; uvGfxClearScreen reads them to size the
// background fill. Not exposed in any header, so declare them here.
extern uvGfxViewport_t gGfxViewports[4];
extern s16 gGfxViewX0;
extern s16 gGfxViewX1;
extern s16 gGfxViewY0;
extern s16 gGfxViewY1;

RECOMP_PATCH void drawScreenBorder(void) {
    uvGfxBindTexture(GFX_STATE_TEXTURE_NONE);
#ifndef ENABLE_ENHANCEMENTS
    uvVtxRect(0, 18, 319, 0);
    uvVtxRect(0, 239, 319, 232);
    uvVtxRect(0, 232, 10, 18);
    uvVtxRect(310, 232, 319, 18);
#endif
}

// Widescreen scene fix.
//
// In widescreen the 3D scene rendered as a sheared parallelogram with pale corner
// wedges, while the HUD stayed correct. Root cause (confirmed via RT64 instrumentation):
// RT64 decides per-projection whether to render full-width or pillarbox-squish-to-centre
// based on whether the (guard-band-expanded) viewport rect covers the whole framebuffer
// width (rt64_framebuffer_renderer.cpp useWideViewport / rt64_projection_processor.cpp).
// The game renders the scene in multiple passes with different guard-band clip ratios
// (uvChan_80204FE4: FRUSTRATIO_1 for the sky/environment, FRUSTRATIO_2 for terrain), and
// the native scene viewport is inset ~5px for the on-screen border. So the low-clip-ratio
// passes' viewport rect fell short of full width and got squished to the centre, while
// the high-clip-ratio passes stayed full-width -- the two scales/offsets disagreeing is
// the "shear", and the squished sky not reaching the corners is the pale wedges.
//
// Fix: for the main scene channels (0/1) force the GPU viewport to span the full
// framebuffer width, so EVERY pass passes RT64's whole-width test and is rendered
// consistently full-width. RT64's normal aspect handling then widens all passes
// uniformly (correct Hor+ widescreen). The screen border is already disabled under
// ENABLE_ENHANCEMENTS (see drawScreenBorder), so the ~5px inset isn't needed.
//
// We also widen the values uvGfxClearScreen reads (gGfxViewX0/X1) so the background
// clear fills the full width to match (that function can't be patched directly -- doing
// so crashes on level load).
RECOMP_PATCH void uvGfxViewport(s32 vpId) {
    uvGfxViewport_t* vp = &gGfxViewports[vpId];
    s32 scissorX0 = vp->x0;
    s32 scissorX1 = vp->x1;
    s32 scissorY0 = vp->y0;
    s32 scissorY1 = vp->y1;

#ifdef ENABLE_ENHANCEMENTS
    if (vpId < 2) {
        // Make the scene's GPU viewport span the full framebuffer (subpixel = px<<2).
        // The native viewport is inset on all four sides (~5px X, a few px Y) to leave
        // room for the on-screen border -- but the border is disabled in enhanced mode,
        // and the game's frustum is built for the full 320x240 framebuffer, so spanning
        // the full extent is the correct, undistorted view.
        //   * Horizontal: this is the shear fix -- every render pass now passes RT64's
        //     "covers whole width?" test identically, so all passes are widened uniformly
        //     instead of some being pillarbox-squished to centre (see block comment above).
        //   * Vertical: removes the top/bottom strips. With the inset, the scene didn't
        //     reach the top/bottom framebuffer edges, so those rows showed leftover
        //     guard-band geometry / stale pixels.
        vp->vp.vp.vtrans[0] = (SCREEN_WIDTH  / 2) << 2;
        vp->vp.vp.vscale[0] = (SCREEN_WIDTH  / 2) << 2;
        vp->vp.vp.vtrans[1] = (SCREEN_HEIGHT / 2) << 2;
        vp->vp.vp.vscale[1] = (SCREEN_HEIGHT / 2) << 2;
        scissorX0 = 0;
        scissorX1 = SCREEN_WIDTH;
        scissorY0 = 0;
        scissorY1 = SCREEN_HEIGHT;
    }
#endif

    gSPViewport(gGfxDisplayListHead++, OS_PHYSICAL_TO_K0(&vp->vp));
    gDPSetScissor(gGfxDisplayListHead++, G_SC_NON_INTERLACE, scissorX0, SCREEN_HEIGHT - scissorY1, scissorX1, SCREEN_HEIGHT - scissorY0);
    gGfxViewX0 = vp->x0;
    gGfxViewX1 = vp->x1;
    gGfxViewY0 = vp->y0;
    gGfxViewY1 = vp->y1;
#ifdef ENABLE_ENHANCEMENTS
    if (vpId < 2) {
        gGfxViewX0 = 0;
        gGfxViewX1 = SCREEN_WIDTH;
        gGfxViewY0 = 0;
        gGfxViewY1 = SCREEN_HEIGHT;
    }
#endif
}

void wide_dummy(void) {
    return;
}

