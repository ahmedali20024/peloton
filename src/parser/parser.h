/*-------------------------------------------------------------------------
 *
 * parser.h
 * file description
 *
 * Copyright(c) 2015, CMU
 *
 * /n-store/src/parser/parser.h
 *
 *-------------------------------------------------------------------------
 */

#pragma once

#include "statements.h"

namespace nstore {
namespace parser {

//===--------------------------------------------------------------------===//
// Parser
//===--------------------------------------------------------------------===//

class Parser {

 public:

  // Parse a given query
  static SQLStatementList* ParseSQLString(const char* sql);
  static SQLStatementList* ParseSQLString(const std::string& sql);

private:
  Parser();

};


} // End parser namespace
} // End nstore namespace
