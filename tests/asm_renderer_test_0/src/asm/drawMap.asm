
public _drawMap

public _curdrawbuffer

extern _blocks
extern _map

; VRAMBUFFER := $D52C00
VRAMBUFFER := $D40000
LCD_WIDTH  := 320
LCD_HEIGHT := 240
MID_X     := LCD_WIDTH/2
MID_Y     := LCD_HEIGHT/2
SIZE_X    := 8
SIZE_Z    := 8
SIZE_Y    := 10

virtual at 0
	BRICK_STAIRS_EAST          rb 1
	BRICK                      rb 1
	COAL_ORE                   rb 1
	DIRT                       rb 1
	GRASS_BLOCK                rb 1
	STONE_BRICK_STAIRS_EAST    rb 1
	STONE_BRICK                rb 1
	STONE                      rb 1
	GLASS_PANE                 rb 1
	GLASS_BLOCK                rb 1
	WATER_SURFACE              rb 1
	WATER_FULL                 rb 1
	STONE_BRICK_2              rb 1
	STONE_BRICK_STAIRS_EAST_2  rb 1
	STONE_STAIRS_EAST          rb 1
end virtual

; void drawMap(){
    ; for(c=0; c<sizeY; c++){
        ; for(a=0; a<sizeX; a++){
            ; for(b=0; b<sizeZ; b++){
                ; x = midX-(a*12)+(b*12);
                ; y = midY+(b*6)+(a*6)-(c*15)+c;
                ; if(map[a][b][c] >= 0) gfx_TransparentSprite(blocks[map[a][b][c]], x, y);
                ; //while (!os_GetCSC());
            ; }

        ; }
    ; }
; }


_drawMap:
	; ; hopefully we won't need to use the shadow registers
	; ld a,i
	; push af
	; pop bc
	; ld (.restore_int),bc
	; di
	push ix,iy
	ld ix,_map
	ld bc,0
	ld e,c
.outer_loop:
; dont bother drawing air blocks
	ld a,(ix)
	inc a
	jq z,.skip_drawing

; make sure to draw this block if its on the +X, +Y or +Z face of the world
	ld a,e
	cp a,SIZE_X-1
	jr nc,.dont_skip_drawing

	ld a,c
	cp a,SIZE_Y-1
	jr nc,.dont_skip_drawing

	ld a,b
	cp a,SIZE_Z-1
	jr nc,.dont_skip_drawing

; dont draw this block if it would be drawn over later by a block of the same type on all forward-facing axis
	ld a,(ix)
	cp a,(ix + 1)
	jr nz,.solidity_check
	cp a,(ix + SIZE_X)
	jr nz,.solidity_check
	cp a,(ix + SIZE_X*SIZE_Z)
	jq z,.skip_drawing

.solidity_check:
; make sure to draw this block if a semisolid block would draw over it later
	ld a,(ix + 1)
; -- Check West facing stair blocks when they're added --
; check for air block
	inc a
	jr z,.dont_skip_drawing
	sub a,GLASS_PANE+1
	cp a,WATER_FULL+1-GLASS_PANE
	jr c,.dont_skip_drawing

	ld a,(ix + SIZE_X)
; check East facing stair blocks
	cp a,BRICK_STAIRS_EAST
	jr z,.dont_skip_drawing
	cp a,STONE_STAIRS_EAST
	jr z,.dont_skip_drawing
	cp a,STONE_BRICK_STAIRS_EAST
	jr z,.dont_skip_drawing
	cp a,STONE_BRICK_STAIRS_EAST_2
	jr z,.dont_skip_drawing
; check for air block
	inc a
	jr z,.dont_skip_drawing
	sub a,GLASS_PANE+1
	cp a,WATER_FULL+1-GLASS_PANE
	jr c,.dont_skip_drawing
	
	ld a,(ix + SIZE_X*SIZE_Z)
; check for air block
	inc a
	jr z,.dont_skip_drawing
	sub a,GLASS_PANE+1
	cp a,WATER_FULL+1-GLASS_PANE
	jq nc,.skip_drawing

.dont_skip_drawing:
	push de,bc
	ld a,e
	; draw a block
	; input ix = map at block position, (a,b,c) = block position
	ld d,a
	ld e,12
	ld h,b
	ld l,e
	mlt de ; a*12
	mlt hl ; b*12
	or a,a
	sbc hl,de
	ex hl,de
	ld hl,MID_X
	or a,a
	sbc hl,de ; hl = x draw position
	push hl

	ld d,a
	ld e,6
	ld h,b
	ld l,e
	mlt de ; a*6
	mlt hl ; b*6
	add hl,de
	ld d,c
	ld e,14
	mlt de ; c*14
	or a,a
	sbc hl,de
	ld de,MID_Y
	add hl,de ; hl = y draw position
	
	ld h,LCD_WIDTH/2
	mlt hl
	add hl,hl ; hl = y*320
	pop de    ; x draw position
	add hl,de ; hl = y*320 + x

	ld de,VRAMBUFFER
_curdrawbuffer:=$-3
	add hl,de
	ex hl,de  ; de = &vram[y*320 + x]
	inc de

	ld hl,_blocks
	ld b,3
	ld c,(ix)
	mlt bc
	add hl,bc
	ld hl,(hl)
	ld bc,28+2
	add hl,bc                ; pointer to (1,1) on the sprite
	ld c,(320-25) and $FF    ; amount to increment vram pointer per row
	inc b
	ld iyh,28                ; number of rows to draw, +1
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
	inc hl        ; skip last pixel of this row and first pixel of the next
	inc hl
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
	inc ix

	inc b
	ld a,b
	sub a,SIZE_X
	jq nz,.outer_loop
	ld b,a

	inc e
	ld a,e
	sub a,SIZE_Z
	jq nz,.outer_loop
	ld e,a

	inc c
	ld a,c
	cp a,SIZE_Y
	jq nz,.outer_loop

	pop iy,ix
	; ld bc,0
; .restore_int:=$-3
	; push bc
	; pop af
	; ret po
	; ei
	ret



