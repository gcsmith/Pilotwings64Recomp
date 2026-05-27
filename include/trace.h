#ifndef __PILOTWINGS64_TRACE_H__
#define __PILOTWINGS64_TRACE_H__

void pilotwings64_trace_entry(uint8_t *rdram, const char *func);
void pilotwings64_trace_return(uint8_t *rdram, const char *func);

#define TRACE_ENTRY()   pilotwings64_trace_entry(rdram, __func__);
#define TRACE_RETURN()  pilotwings64_trace_return(rdram, __func__);

#endif // __PILOTWINGS64_TRACE_H__

