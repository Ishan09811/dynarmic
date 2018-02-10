/* This file is part of the dynarmic project.
 * Copyright (c) 2018 MerryMage
 * This software may be used and distributed according to the terms of the GNU
 * General Public License version 2 or any later version.
 */

#include "frontend/A64/translate/impl/impl.h"

namespace Dynarmic::A64 {

bool TranslatorVisitor::XTN(bool Q, Imm<2> size, Vec Vn, Vec Vd) {
    if (size == 0b11) {
        return ReservedValue();
    }
    const size_t esize = 8 << size.ZeroExtend<size_t>();
    const size_t datasize = 64;
    const size_t part = Q ? 1 : 0;

    const IR::U128 operand = V(2 * datasize, Vn);
    const IR::U128 result = ir.VectorNarrow(2 * esize, operand);

    Vpart(datasize, Vd, part, result);
    return true;
}

} // namespace Dynarmic::A64
