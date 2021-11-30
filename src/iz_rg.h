typedef u64 RG_ID;

#define RG_INVALID_ID 0
#define RG_NEXT_ID_INTERVAL U16_MAX
#define RG_NEXT_ID ((__COUNTER__ + 1) * RG_NEXT_ID_INTERVAL)

typedef struct RG_Panel_State
{
    RG_ID id;
    V2 scroll;
} RG_Panel_State;

typedef struct RG_State
{
    RG_ID hot_id;
    RG_ID active_id;
    
    RG_ID current_panel_id;
} RG_State;

internal bool
RG_DrawButton(RG_ID id, Rect box, String title)
{
}

internal void
RG_BeginPanel(RG_ID id, String title)
{
    Platform->PushFilledRectZ();
}

internal void
RG_EndPanel()
{
}

internal void
RG_PushRow(u32 column_count, i32* column_bias)
{
    if (columns == 0)
    {
    }
    
    else
    {
    }
}

internal bool
RG_PushButton(RG_ID id, String text)
{
}

internal void
RG_BeginFrame()
{
}

internal void
RG_EndFrame()
{
}