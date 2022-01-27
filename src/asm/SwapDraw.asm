
public _SwapDraw

extern _curdrawbuffer

extern _gfx_SwapDraw

VRAM       :=  $D40000
VRAMBUFFER :=  $D52C00
_SwapDraw:   ; swap draw buffer locations for iso renderer, then run gfx_SwapDraw
	ld a,(_curdrawbuffer+2)
	cp a,VRAM shr 16
	ld hl,VRAMBUFFER
	jr z,.swapfromscreen
	ld hl,VRAM
.swapfromscreen:
	ld (_curdrawbuffer),hl
	jq _gfx_SwapDraw

