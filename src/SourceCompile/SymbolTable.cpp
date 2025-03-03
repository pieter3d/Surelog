/*
 Copyright 2019 Alain Dargelas

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

/*
 * File:   SymbolTable.cpp
 * Author: alain
 *
 * Created on March 6, 2017, 11:10 PM
 */
#include "SourceCompile/SymbolTable.h"

using namespace SURELOG;

SymbolTable::SymbolTable() : m_idCounter(1) {
  m_id2SymbolMap.push_back(getBadSymbol());
  m_symbol2IdMap.insert(std::make_pair(getBadSymbol(), 0));
}

SymbolTable::~SymbolTable() {}

const std::string& SymbolTable::getBadSymbol() {
  static const std::string k_badSymbol("@@BAD_SYMBOL@@");
  return k_badSymbol;
}

const std::string& SymbolTable::getEmptyMacroMarker() {
  static const std::string k_emptyMacroMarker("@@EMPTY_MACRO@@");
  return k_emptyMacroMarker;
}

SymbolId SymbolTable::registerSymbol(const std::string& symbol) {
  // TODO: use std::string_view and heterogeneous lookup
  const auto inserted = m_symbol2IdMap.insert({symbol, m_idCounter});
  if (inserted.second) {
    m_id2SymbolMap.emplace_back(symbol);
    m_idCounter++;
  }
  return inserted.first->second;
}

SymbolId SymbolTable::getId(const std::string& symbol) const {
  // TODO: use std::string_view and heterogeneous lookup
  auto found = m_symbol2IdMap.find(symbol);
  return (found == m_symbol2IdMap.end()) ? getBadId() : found->second;
}

const std::string& SymbolTable::getSymbol(SymbolId id) const {
  if (id >= m_id2SymbolMap.size()) return getBadSymbol();
  return m_id2SymbolMap[id];
}
