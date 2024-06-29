#pragma once

typedef enum
{
    EVENT_NONE,
    SET_POINT,
    MATCH_POINT,
} event_t;

void tennis_event_init(void);
event_t tennis_event_get(void);
void tennis_event_set(event_t new_event);
void tennis_event_check(void);