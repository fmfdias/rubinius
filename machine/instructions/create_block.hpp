#include "interpreter/instructions.hpp"

#include "builtin/block_environment.hpp"
#include "builtin/code_db.hpp"

namespace rubinius {
  namespace instructions {
    inline bool create_block(STATE, CallFrame* call_frame, intptr_t literal) {
      Object* code_or_id = reinterpret_cast<Object*>(literal);
      CompiledCode* code = 0;

      if(!(code = try_as<CompiledCode>(code_or_id))) {
        code = CodeDB::load(state, as<String>(code_or_id));
        // TODO: instructions
        // store_literal(reinterpret_cast<opcode>(code));
      }

      Object* be = BlockEnvironment::under_call_frame(state, code, call_frame->machine_code);

      CHECK_AND_PUSH(be);
    }
  }
}