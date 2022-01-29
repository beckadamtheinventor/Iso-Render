
public _iso_Init
public _iso_DrawMap
public _iso_SetDraw
public _iso_SwapDraw

VRAM       := $D40000
VRAMBUFFER := $D52C00
LCD_WIDTH  := 320
LCD_HEIGHT := 240
MID_X      := 160
MID_Y      := 128
SIZE_X     := 8
SIZE_Z     := 8
SIZE_Y     := 10

;typedef struct __iso_config_t {
;	gfx_sprite_t *blocks;
;	uint8_t   first_semisolid;
;	uint8_t   num_semisolids;
;	uint8_t   first_east_semisolid;
;	uint8_t   num_east_semisolids;
;	uint8_t   first_west_semisolid;
;	uint8_t   num_west_semisolids;
;}iso_config_t;

;---------------------------------------------
; bool iso_Init(iso_config_t *config):
; returns true if success.
_iso_Init:
	pop bc
	ex (sp),hl
	push bc
	ld de,(hl)
	ld (_blocks_smc),de
	inc hl
	inc hl
	inc hl
	ld a,(hl)
	inc hl
	ld (FIRST_SEMISOLID__smc1),a
	ld (FIRST_SEMISOLID__smc2),a
	ld (FIRST_SEMISOLID__smc3),a
	ld a,(hl)
	inc hl
	ld (NUM_SEMISOLIDS__smc1),a
	ld (NUM_SEMISOLIDS__smc2),a
	ld a,(hl)
	inc hl
	ld (FIRST_EAST_SEMISOLID),a
	ld a,(hl)
	inc hl
	ld (NUM_EAST_SEMISOLIDS),a
	ld a,(hl)
	inc hl
	ld (FIRST_WEST_SEMISOLID),a
	ld a,(hl)
	inc hl
	ld (NUM_WEST_SEMISOLIDS),a
	
	ld a,1
	ld (HAS__iso_INIT_BEEN_CALLED),a
	ret

;---------------------------------------------
; bool iso_DrawMap(uint8_t *map);
; returns false if iso_Init hasn't been called yet, otherwise true.
_iso_DrawMap:
	ld a,0
HAS__iso_INIT_BEEN_CALLED := $-1
	or a,a
	ret z
	; ; hopefully we won't need to use the shadow registers
	; ld a,i
	; push af
	; pop bc
	; ld (.restore_int),bc
	; di
	pop bc
	ex (sp),hl
	push bc
	push iy,hl
	ex (sp),ix
	ld bc,0
	ld e,c
.outer_loop:
; dont bother drawing air blocks
	ld a,(ix)
	or a,a
	jq z,.skip_drawing

; make sure to draw this block if its on a forward face of the world
	ld a,e
	cp a,SIZE_X-1
END_X__smc1 := $-1
	jr z,.dont_skip_drawing

	ld a,c
	cp a,SIZE_Y-1
END_Z__smc1 := $-1
	jr z,.dont_skip_drawing

	ld a,b
	cp a,SIZE_Z-1
	jr z,.dont_skip_drawing

; dont draw this block if it would be drawn over later by a block of the same type on all forward-facing axis
	ld a,(ix)
	cp a,(ix + 1)
NEXT_X__smc1 := $-1
	jr nz,.solidity_check
	cp a,(ix + SIZE_X)
NEXT_Z__smc1 := $-1
	jr nz,.solidity_check
assert SIZE_X*SIZE_Z < 257
if SIZE_X*SIZE_Z < 128
	cp a,(ix + SIZE_X*SIZE_Z)
else if SIZE_X*SIZE_Z < 257
	lea iy,ix + 127
	lea hl,iy + 127
	inc hl
	if SIZE_X*SIZE_Z = 256
		inc hl
	end if
	cp a,(hl)
end if
	jq z,.skip_drawing

.solidity_check:
; make sure to draw this block if a semisolid block would draw over it later
; Check block West
	ld a,(ix + 1)
NEXT_X__smc2 := $-1
; check for semisolid block West
	or a,a
	jr z,.dont_skip_drawing
	sub a,0
FIRST_SEMISOLID__smc1 := $-1
	cp a,0
NUM_SEMISOLIDS__smc1 := $-1
	jr c,.dont_skip_drawing
; check for West-only semisolid block West (only semisolid when viewed from the West)
	ld a,(ix + 1)
NEXT_X__smc3 := $-1
	sub a,0
FIRST_WEST_SEMISOLID := $-1
	cp a,0
NUM_WEST_SEMISOLIDS := $-1
	jr c,.dont_skip_drawing

; Check block East
	ld a,(ix + SIZE_X)
NEXT_Z__smc2 := $-1
; check for semisolid block East
	or a,a
	jr z,.dont_skip_drawing
	sub a,0
FIRST_SEMISOLID__smc2 := $-1
	cp a,0
NUM_SEMISOLIDS__smc2 := $-1
	jr c,.dont_skip_drawing
	ld a,(ix + SIZE_X)
NEXT_Z__smc3 := $-1
; check for East-only semisolid block East (only semisolid when viewed from the East)
	sub a,0
FIRST_EAST_SEMISOLID := $-1
	cp a,0
NUM_EAST_SEMISOLIDS := $-1
	jr c,.dont_skip_drawing

; Check block Up
assert SIZE_X*SIZE_Z < 257
if SIZE_X*SIZE_Z < 128
	ld a,(ix + SIZE_X*SIZE_Z)
else if SIZE_X*SIZE_Z < 257
	lea iy,ix + 127
	lea hl,iy + 127
	inc hl
	if SIZE_X*SIZE_Z = 256
		inc hl
	end if
	ld a,(hl)
end if

; check for air block
	or a,a
	jr z,.dont_skip_drawing
	sub a,0
FIRST_SEMISOLID__smc3 := $-1
	cp a,0
NUM_SEMISOLIDS__smc3 := $-1
	jp nc,.skip_drawing

.dont_skip_drawing:
	push de,bc
	ld a,e

	; draw a block
	; input ix = map at block position, (a,b,c) = block position
	ld d,a
	ld e,12
A_MULT_12_smc := $-1
	ld h,b
	ld l,12
B_MULT_12_smc := $-1

	mlt de ; a*12
	mlt hl ; b*12
	or a,a
	sbc.s hl,de
	ex hl,de
	ld hl,MID_X
	or a,a
	sbc.s hl,de ; hl = x draw position
	ex hl,de
	ld iyh,d
	ld iyl,e ; save x position for later

	ld d,a
	ld e,6
A_MULT_6_smc := $-1
	ld h,b
	ld l,6
B_MULT_6_smc := $-1
	mlt de ; a*6
	mlt hl ; b*6
	add hl,de
	ld d,c
	ld e,14
	mlt de ; c*14
	or a,a
	sbc.s hl,de
	ld de,MID_Y
	add hl,de ; l = y draw position

	ld d,iyh
	ld e,iyl  ; de = x draw position
	ld h,LCD_WIDTH/2
	mlt hl
	add hl,hl ; hl = y*320
	add hl,de ; hl = y*320 + x

	ld de,VRAM
_curdrawbuffer:=$-3
	add hl,de
	ex hl,de  ; de = &vram[y*320 + x]
	inc de

	ld hl,0
_blocks_smc:=$-3
	ld b,3
	ld c,(ix)
	mlt bc
	add hl,bc
	ld hl,(hl)
	inc hl
	inc hl
	ld c,(320-25) and $FF    ; amount to increment vram pointer per row
	inc b
	ld iyh,27                ; number of rows to draw
	jr .sprite_loop_outer
.sprite_loop:
	inc de
	dec iyl
	jr nz,.sprite_loop_entry
	ex hl,de
	add hl,bc
	ex hl,de
	dec iyh
	jr z,.sprite_loop_end
	; inc hl        ; skip last pixel of this row and first pixel of the next
	; inc hl
.sprite_loop_outer:
	ld iyl,25                ; number of columns to draw 
.sprite_loop_entry:
	ld a,(hl)
	inc hl
	or a,a
	jr z,.sprite_loop
	ld (de),a
	jr .sprite_loop
.sprite_loop_end:
	pop bc,de
.skip_drawing:
	lea ix,ix+1
MAP_IX_INCREMENT_INNER := $-1

	inc b
	ld a,b
	sub a,SIZE_X
	jq nz,.outer_loop
	ld b,a
	lea ix,ix+0
MAP_IX_INCREMENT_OUTER := $-1

	inc e
	ld a,e
	sub a,SIZE_Z
	jq nz,.outer_loop
	lea ix,ix+0
MAP_IX_INCREMENT_UPWARD := $-1
	ld e,a

	inc c
	ld a,c
	cp a,SIZE_Y
	jq nz,.outer_loop

	pop ix,iy
	; ld bc,0
; .restore_int:=$-3
	; push bc
	; pop af
	; ret po
	; ei
	ret

;---------------------------------------------
; set draw location for iso renderer
; void *iso_SetDraw(uint8_t loc);
; 0 for vram, 1 for buffer
_iso_SetDraw:
	pop bc
	ex (sp),hl
	push bc
	ld a,l
	or a,a
	jr z,_iso_SwapDraw.tovram
	inc a
	jr _iso_SwapDraw.tovrambuffer
;---------------------------------------------
; swap draw buffer location for iso renderer
_iso_SwapDraw:
	ld a,(_curdrawbuffer+2)
	cp a,VRAM shr 16
.tovrambuffer:
	ld hl,VRAMBUFFER
	jr z,.swapfromscreen
.tovram:
	ld hl,VRAM
.swapfromscreen:
	ld (_curdrawbuffer),hl
	ret

