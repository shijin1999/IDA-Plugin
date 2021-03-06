
#ifndef __M740_HPP
#define __M740_HPP

#include "../idaidp.hpp"
#include "ins.hpp"
#include <diskio.hpp>
#include <frame.hpp>

// flags for insn.auxpref
#define INSN_DISPL_INDX        0x00000001    // indirect X
#define INSN_DISPL_INDY        0x00000002    // indirect Y
#define INSN_DISPL_ZPX         0x00000004    // zero page X
#define INSN_DISPL_ZPY         0x00000008    // zero page Y
#define INSN_DISPL_ABSX        0x00000010    // absolute X
#define INSN_DISPL_ABSY        0x00000020    // absolute Y

inline bool is_displ_indx(const insn_t &insn) { return (insn.auxpref & INSN_DISPL_INDX) != 0; }
inline bool is_displ_indy(const insn_t &insn) { return (insn.auxpref & INSN_DISPL_INDY) != 0; }
inline bool is_displ_zpx(const insn_t &insn)  { return (insn.auxpref & INSN_DISPL_ZPX) != 0; }
inline bool is_displ_zpy(const insn_t &insn)  { return (insn.auxpref & INSN_DISPL_ZPY) != 0; }
inline bool is_displ_absx(const insn_t &insn) { return (insn.auxpref & INSN_DISPL_ABSX) != 0; }
inline bool is_displ_absy(const insn_t &insn) { return (insn.auxpref & INSN_DISPL_ABSY) != 0; }

// flags for insn.Op[n].specflag1
#define OP_ADDR_SP           0x00000001    // special page
#define OP_ADDR_IND          0x00000002    // indirect address
#define OP_ADDR_R            0x00000010    // read access
#define OP_ADDR_W            0x00000020    // write access
#define OP_IMM_BIT           0x00000004    // immediate bit index

inline bool is_addr_sp(const op_t &op) { return (op.specflag1 & OP_ADDR_SP) != 0; }
inline bool is_addr_ind(const op_t &op) { return (op.specflag1 & OP_ADDR_IND) != 0; }
inline bool is_addr_read(const op_t &op) { return (op.specflag1 & OP_ADDR_R) != 0; }
inline bool is_addr_write(const op_t &op) { return (op.specflag1 & OP_ADDR_W) != 0; }

// flags for ash.uflag
#define UAS_SEGM            0x0001   // segments are named "segment XXX"
#define UAS_RSEG            0x0002   // segments are named "rseg XXX"
#define UAS_INDX_NOSPACE    0x0004   // no spaces between operands in indirect X addressing mode

// 740 registers
enum m740_registers
{
  rA,            // accumulator
  rX,            // index register X
  rY,            // index register Y
  rS,            // stack pointer
  rPS,           // processor status register
  rVcs, rVds     // these 2 registers are required by the IDA kernel
};

// 740 phrases
enum m740_phrases {};

extern qstring device;

// exporting our routines
void idaapi m740_header(outctx_t &ctx);
void idaapi m740_footer(outctx_t &ctx);
void idaapi m740_segstart(outctx_t &ctx, segment_t *seg);
int idaapi ana(insn_t *_insn);
int idaapi emu(const insn_t &insn);

#endif /* __M740_HPP */
