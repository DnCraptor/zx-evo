`include "../include/tune.v"

// This is the Tile Sprite Processing Unit

// Tiles map address:
//  bits    desc
//  20:13   tmpage
//  12:

// Graphics address:
//  bits    desc
//  20:13   Xgpage
//  15:7    line (bits 15:13 are added) - 512 lines
//  6:0     word within line - 128 words = 512 pixels

// - tiles - (256x192, offset0 = 128, offset1 = 0)
// clk			|誉_覧__覧__覧__覧__覧__覧__覧__覧__覧__覧__覧__覧__覧__覧__覧__覧__� ~ 誉_覧__覧__覧__覧__覧__覧__覧__覧__覧__覧__覧__�
// c0-3			|<c3><c0><c1><c2><c3><c0><c1><c2><c3><c0><c1><c2><c3><c0><c1><c2><c3> ~ <c0><c1><c2><c3><c0><c1><c2><c3><c0><c1><c2><c3>
// layer		|<t0><t0><t0><t0><t0><t0><t0><t0><t0><t0><t0><t0><t0><t0><t0><t0><t0> ~ <t0><t0><t0><t1><t1><t1><t1><t1><t1><t1><t1><t1>
// start		|覧覧________________________________________________________________ ~ ________________________________________________
// tile_end  	|____________________________________________________________________ ~ ________覧覧____________________________________
// layer_end_r	|xxxx________________________________________________________________ ~ ____________覧覧________________________________
// tile_start	|覧覧________________________________________________________________ ~ ____________覧覧________________________________
// tmb_valid	|____覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧 ~ 覧覧覧覧覧覧____覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧
// tsr_rdy		|xxxx覧覧____________________________________覧覧____________________ ~ ________覧覧____________________________覧覧____
// yscrl_rd		|覧覧覧覧覧覧覧覧覧覧覧覧____________________覧覧覧覧________________ ~ 覧覧覧覧覧覧覧覧覧覧____________________覧覧____
// tile_go		|____覧覧____________________________________覧覧____________________ ~ ________覧覧____________________________覧覧____
// tpos_x		|<10><11><12><13><14><15><15><15><15><15><15><16><17><17><17><17><17> ~ <2F><30><31><00><01><01><01><01><01><01><02><02>
// tmb_raddr	|<10><11><12><13><14><15><15><15><15><15><15><16><17><17><17><17><17> ~ <2F><30><31><00><01><01><01><01><01><01><02><02>
// tpos_x_r		|xxxx<10><11><12><13><14><15><15><15><15><15><15><16><17><17><17><17> ~ <2E><2F><30><30><00><01><01><01><01><01><01><02>
// tmb_rdata	|xxxx<10><11><12><13><14><15><15><15><15><15><15><16><17><17><17><17> ~ <2E><2F><30><30><00><01><01><01><01><01><01><02>
// t_act		|xxxx覧覧________________覧覧覧覧覧覧覧覧覧覧覧覧____覧覧覧覧覧覧覧覧 ~ ________覧覧覧覧____覧覧覧覧覧覧覧覧覧覧覧覧覧覧
// t_next		|____覧覧覧覧覧覧覧覧覧覧____________________覧覧覧覧________________ ~ 覧覧覧覧覧覧____覧覧____________________覧覧____
// tx			|<00><01><02><03><04><05><05><05><05><05><05><06><07><07><07><07><07> ~ <1F><20><21><00><01><01><01><01><01><01><02><02>
// tx_r			|xxxx<00><01><02><03><04><05><05><05><05><05><05><06><07><07><07><07> ~ <1E><1F><20><20><00><01><01><01><01><01><01><02>
// tile_end		|xxxx________________________________________________________________ ~ ________覧覧____________________________________
// tiles0		|xxxx覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧 ~ 覧覧覧覧覧覧____________________________________
// tiles1		|xxxx________________________________________________________________ ~ ____________覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧
//				|

// - sprites -
// clk			|誉_覧__覧__覧__覧__覧__覧__覧__覧__覧__覧__覧__覧__覧__覧__覧__覧__覧__覧__覧__覧__覧__覧__覧__覧__� ~ 誉_覧__覧__覧__覧__�
// c0-3			|<c3><c0><c1><c2><c3><c0><c1><c2><c3><c0><c1><c2><c3><c0><c1><c2><c3><c0><c1><c2><c3><c0><c1><c2><c3> ~ <c0><c1><c2><c3><c3>
// layer		|<s0><s0><s0><s0><s0><s0><s0><s0><s0><s0><s0><s0><s0><s0><s0><s0><s0><s0><s0><s0><s1><s1><s1><s1><s1> ~ <s1><s1><s1><s2><s2>
// start		|覧覧________________________________________________________________________________________________ ~ ____________________
// sprt_end  	|____________________________________________________覧覧____________________________________________ ~ ____________覧覧覧覧  = sprt_done || (spr_next && s_leap) || (sprt_go && s_leap_r)
// sprt_done  	|____________________________________________________________________________________________________ ~ ____________覧覧覧覧  = sreg == 7'd126
// sprt_done_r 	|xxxx________________________________________________________________________________________________ ~ ________________覧覧
// layer_end_r	|xxxx____________________________________________________覧覧________________________________________ ~ ____________覧覧覧覧
// sreg			|<00><01><02><03><06><09><0A><0B><0B><0B><0B><0C><0F><10><11><11><11><11><11><12><13><14><14><14><14> ~ <79><7A><7B><7E><7E>
// sf_data		|xxxx<00><01><02><03><06><09><0A><0B><0B><0B><0B><0C><0F><10><11><11><11><11><11><12><13><14><14><14> ~ <78><79><7A><7B><7E>
// sreg*		|xxxx<00><01><02><00><00><00><01><02><02><02><02><00><00><01><02><02><02><02><02><00><01><02><02><02> ~ <00><01><02><00><00>
// sf0_valid	|____覧覧________覧覧覧覧覧覧____________________覧覧覧覧________________________覧覧________________ ~ 覧覧________________
// sf1_valid	|________覧覧________________覧覧________________________覧覧________________________覧覧             ~ ____覧覧____________
// sf2_valid	|____________覧覧________________覧覧覧覧覧覧覧覧____________覧覧覧覧覧覧覧覧覧覧________覧覧覧覧覧覧 ~ ________覧覧________
// s_visible	|xxxx覧覧xxxxxxxx________覧覧xxxxxxxxxxxxxxxxxxxx____覧覧xxxxxxxxxxxxxxxxxxxxxxxx覧覧xxxxxxxxxxxxxxxx ~ 覧覧xxxxxxxx________
// sreg_next	|xxxx覧覧覧覧覧覧________覧覧覧覧____________覧覧____覧覧覧覧________________覧覧覧覧覧覧____________ ~ 覧覧覧覧覧覧________  = sprt_go || (sf0_valid && s_act) || sf1_valid
// spr_next		|xxxx____________覧覧覧覧________________________覧覧________________________________________________ ~ ____________________  = sf0_valid && !s_act
// tsr_rdy		|xxxx覧覧覧覧覧覧____________________________覧覧____________________________覧覧____________________ ~ ________覧覧________
// sprt_go		|____________覧覧____________________________覧覧____________________________覧覧____________________ ~ ________覧覧________  = sprites && sf2_valid && tsr_rdy
// s_leap		|xxxx____xxxxxxxx____________xxxxxxxxxxxxxxxxxxxx____覧覧xxxxxxxxxxxxxxxxxxxxxxxx____xxxxxxxxxxxxxxxx ~ 覧覧xxxxxxxxxxxxxxxx
// s_leap_r		|xxxxxxxx________________________________________________覧覧覧覧覧覧覧覧覧覧覧覧覧覧________________ ~ ____覧覧覧覧覧覧覧覧


// to do:
// - fix Yscrolls array
// - draw DRAM cycles on-screen to determine how and what works
// - code a/r Ys for tiles
// - write global test for TS
// - DMA for Sfile


module video_ts (

// clocks
	input wire clk,

// video controls
	input wire start,
	input wire [8:0] line,      // 	= vcount - vpix_beg + 9'b1;

// video config
	input wire [7:0] tsconf,
    input wire [7:0] t0gpage,
    input wire [7:0] t1gpage,
    input wire [7:0] sgpage,
	input wire [5:0] num_tiles,
	input wire [8:0] t0x_offs,
	input wire [8:0] t1x_offs,
	input wire [2:0] t0y_offs,
	input wire [2:0] t1y_offs,
	input wire [1:0] t0_palsel,
	input wire [1:0] t1_palsel,

// SFYS interface
	input  wire  [7:0] sfys_addr_in,
	input  wire [15:0] sfys_data_in,
	input  wire sfys_we,
	input  wire [6:0] tys_data_x,
	input  wire tys_data_s,
	output wire [5:0] tys_data_f,

// TMbuf interface
	output wire [8:0] tmb_raddr,
	input wire [15:0] tmb_rdata,

// renderer interface
	output wire tsr_go,
	output wire [5:0] tsr_addr,     // graphics address within the line
    output wire [8:0] tsr_line,     // bitmap line
    output wire [7:0] tsr_page,     // bitmap 1st page
    output wire [8:0] tsr_x,        // addr in buffer (0-359 visibles)
    output wire [2:0] tsr_xs,       // size (8-64 pix)
    output wire tsr_xf,             // X flip
    output wire [3:0] tsr_pal,		// palette
	input wire tsr_rdy              // renderer is done and ready to receive a new task

);


// sprite descriptor fields
  // R0
	wire [8:0]  s_ycrd	= sfys_data_out[8:0];
	wire [2:0]  s_ysz	= sfys_data_out[11:9];
	wire        s_act	= sfys_data_out[13];
	wire        s_leap	= sfys_data_out[14];
	wire        s_yflp	= sfys_data_out[15];
  // R1
	wire [8:0]  s_xcrd	= sfys_data_out[8:0];
	wire [2:0]  s_xsz	= sfys_data_out[11:9];
	wire        s_xflp	= sfys_data_out[15];
  // R2
	wire [11:0] s_tnum	= sfys_data_out[11:0];
	wire [3:0]	s_pal	= sfys_data_out[15:12];


// tile descriptor fields
	wire [11:0] t_tnum	= tmb_rdata[11:0];
	wire [1:0]	t_pal	= tmb_rdata[13:12];
	wire        t_xflp	= tmb_rdata[14];
	wire        t_yflp	= tmb_rdata[15];


// config
	wire s_en = tsconf[7];
	wire t1_en = tsconf[6];
	wire t0_en = tsconf[5];
	wire t1z_en = tsconf[3];
	wire t0z_en = tsconf[2];
	wire t1ys_en = tsconf[1];
	wire t0ys_en = tsconf[0];


// TS renderer interface
    assign tsr_x = sprites ? sprt_x : tile_x;
    assign tsr_xs = sprites ? sprt_xs : tile_xs;
    assign tsr_xf = sprites ? sprt_xf : tile_xf;
    assign tsr_go = sprites ? sprt_go : tile_go;
    assign tsr_page = sprites ? sprt_page : tile_page;
    assign tsr_line = sprites ? sprt_line : tile_line;
    assign tsr_addr = sprites ? sprt_addr : tile_addr;
    assign tsr_pal = sprites ? sprt_pal : tile_pal;


// --- Tiles ---

    // TSR strobe for tiles
	wire tile_go = tiles && t_act && tmb_valid && tsr_rdy;

    // TSR values for tiles
    wire [7:0] tile_page = tiles0 ? t0gpage : t1gpage;
    wire [8:0] tile_line = {t_tnum[11:6], (t_line[2:0] ^ {3{t_yflp}})};
    wire [5:0] tile_addr = t_tnum[5:0];
    wire tile_xf = t_xflp;
    wire [2:0] tile_xs = 3'd0;
    wire [3:0] tile_pal = {tiles0 ? t0_palsel : t1_palsel, t_pal};

	// tile layers
	wire tile_start = layer_new && tiles;		// 1st cycle when tile layer is active
	wire tile_end = (tiles0 && !t0_en) || (tiles1 && !t1_en)  || (tx == num_tiles);
	wire tile_done = tile_end && tiles1;

	reg tile_done_r;
	always @(posedge clk)
		if (start)
			tile_done_r <= 1'b0;
		else if (tile_done)
			tile_done_r <= 1'b1;

	// tile X processing
    wire t_act = |t_tnum || (tiles0 ? t0z_en : t1z_en);
	wire t_next = tile_go || (!t_act && tmb_valid);
	wire tmb_valid = !layer_new && !tile_done_r;

    // TMB address
    assign tmb_raddr = {t_line[4:3], tpos_x, tiles1};
	wire [5:0] tpos_x = layer_new ? tx_offs[8:3] : (tpos_x_r + t_next);		// X position in tilemap
    wire [8:0] tx_offs = tiles0 ? t0x_offs : t1x_offs;

	reg [5:0] tpos_x_r;
	always @(posedge clk)
        tpos_x_r <= tpos_x;

    // tile X coordinate
    wire [8:0] tile_x = {tx_r, 3'd0} - tx_offs[2:0];
	wire [5:0] tx = layer_new ? 6'd0 : (tx_r + t_next);		// X coordinate at the screen, higher bits (lower are offset finetune)

	reg [5:0] tx_r;
	always @(posedge clk)
        tx_r <= tx;

	// tile Y geometry
	wire [8:0] t_line = line + ty_offset;

	// tile Y scrollers
	wire [2:0] ty_offset = tys_en ? tys_data[2:0] : ty_offs;
	wire [2:0] ty_offs = tiles0 ? t0y_offs : t1y_offs;

	// SFYS addressing
	wire [2:0] tys_data = yscrl_rd_r ? sfys_data_out[2:0] : tys_data_r;
	wire yscrl_rd = tys_en && (tile_start || t_next);
	wire tys_en = tiles0 ? t0ys_en : t1ys_en;

	reg [2:0] tys_data_r;
	always @(posedge clk)
		if (yscrl_rd_r)
			tys_data_r <= sfys_data_out[2:0];

	reg yscrl_rd_r;
	always @(posedge clk)
		yscrl_rd_r <= yscrl_rd || tys_data_s;


// --- Sprites ---

    // TSR strobe for sprites
	wire sprt_go = sprites && sf2_valid && tsr_rdy;

	// TSR values for tiles
    wire [8:0] sprt_x = sprt_x_r;
    wire [2:0] sprt_xs = sprt_xs_r;
    wire sprt_xf = sprt_xf_r;
    wire [7:0] sprt_page = sgpage;
    wire [8:0] sprt_line = s_bmline;
    wire [5:0] sprt_addr = s_tnum[5:0];
    wire [3:0] sprt_pal = s_pal;

	// sprite layers
	wire sprt_end = sprt_done || (spr_next && s_leap) || (sprt_go && s_leap_r);
	wire sprt_done = sreg == 7'd126;

	reg sprt_done_r;
	always @(posedge clk)
		if (start)
			sprt_done_r <= 1'b0;
		else if (sprt_done)
			sprt_done_r <= 1'b1;

	// sprite Y geometry
	wire [8:0] s_bmline = {s_tnum[11:6], 3'b0} + s_bmline_offset_r;
	wire [5:0] s_bmline_offset = s_yflp ? (s_ysize - s_line[5:0]) : s_line[5:0];
    wire [8:0] s_line = line + s_ycrd;					// 3-6 (depending on its size) lower bits - line number within sprite
    wire s_visible = (s_line <= s_ysize) && s_act;
	wire [5:0] s_ysize = {s_ysz, 3'b111};

	// SFile regs counter
	wire [6:0] sreg = start ? 7'd0 : sreg_r + (sreg_next ? 7'd1 : (spr_next ? 7'd3 : 7'd0));

	reg [6:0] sreg_r;
	always @(posedge clk)
		sreg_r <= sreg;

	// SFile regs processing
	wire spr_next = sf0_valid && !s_visible;
	wire sreg_next = sprt_go || (sf0_valid && s_visible) || sf1_valid;

	// SFile regs validity
	wire sf0_valid = !start && !yscrl_rd_r && sf_valid_r[0] && !sprt_done_r;
	wire sf1_valid = !start && !yscrl_rd_r && sf_valid_r[1];
	wire sf2_valid = !start && !yscrl_rd_r && sf_valid_r[2];

	reg [2:0] sf_valid_r;
	always @(posedge clk)
		if (start)
			sf_valid_r <= 3'b001;

		else if (sreg_next)
			sf_valid_r <= {sf_valid_r[1:0], sf_valid_r[2]};

	// SFile regs latching
    reg [8:0] sprt_x_r;
    reg [5:0] s_bmline_offset_r;
    reg [2:0] sprt_xs_r;
    reg sprt_xf_r;
	reg s_leap_r;
	always @(posedge clk)
	begin
		if (sf0_valid)
		begin
			s_leap_r <= s_leap;
			s_bmline_offset_r <= s_bmline_offset;
		end

		if (sf1_valid)
		begin
			sprt_x_r <= s_xcrd;
			sprt_xs_r <= s_xsz;
			sprt_xf_r <= s_xflp;
		end
	end


// layers
	wire [2:0] layer = start ? lnxt[BEG] : (layer_end_r ? lnxt[layer_r] : layer_r);
	wire layer_new = layer_end_r || start;
    wire layer_end = (sprites && sprt_end) || (tiles && tile_end);
	wire sprites = (layer == S0) || (layer == S1) || (layer == S2);
    wire tiles = tiles0 || tiles1;
    wire tiles0 = (layer == T0);
    wire tiles1 = (layer == T1);

	reg [2:0] layer_r;
	reg layer_end_r;
	always @(posedge clk)
		begin
			layer_r <= layer;
			layer_end_r <= layer_end;
		end


	localparam BEG = 3'd0;
	localparam S0 = 3'd1;
	localparam T0 = 3'd2;
	localparam S1 = 3'd3;
	localparam T1 = 3'd4;
	localparam S2 = 3'd5;
	localparam END = 3'd6;
	localparam FND = 3'd7;

	wire [2:0] lnxt[0:7];
	assign lnxt[BEG] = s_en ? S0 : t0_en ? T0 : t1_en ? T1 : END;
	assign lnxt[S0]  = t0_en ? T0 : s_en ? S1 : t1_en ? T1 : END;
	assign lnxt[T0]  = s_en ? S1 : t1_en ? T1 : END;
	assign lnxt[S1]  = t1_en ? T1 : s_en ? S2 : END;
	assign lnxt[T1]  = s_en ? S2 : END;
	assign lnxt[S2]  = END;
	assign lnxt[END] = END;
	assign lnxt[FND] = END;


// SFile / YScrolls
	wire [7:0] sfys_addr_out = {(yscrl_rd || tys_data_s), tys_data_s ? tys_data_x : (yscrl_rd ? {tiles1, tpos_x} : sreg)};
	wire [15:0] sfys_data_out;
	assign tys_data_f = sfys_data_out[8:3];

video_sf_ys video_sf_ys (
	.clock	    (clk),
	.wraddress	(sfys_addr_in),
	.data		(sfys_data_in),
	.wren		(sfys_we),
	.rdaddress	(sfys_addr_out),
	.q			(sfys_data_out)
);


endmodule
