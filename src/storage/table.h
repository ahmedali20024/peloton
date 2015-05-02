/*-------------------------------------------------------------------------
 *
 * table.h
 * file description
 *
 * Copyright(c) 2015, CMU
 *
 * /n-store/src/storage/table.h
 *
 *-------------------------------------------------------------------------
 */

#pragma once

#include "catalog/manager.h"
#include "storage/tile_group.h"
#include "storage/backend_vm.h"

#include <string>

namespace nstore {
namespace storage {

//===--------------------------------------------------------------------===//
// Table
//===--------------------------------------------------------------------===//

/**
 * Represents a group of tile groups logically vertically contiguous.
 *
 * <Tile Group 1>
 * <Tile Group 2>
 * ...
 * <Tile Group n>
 *
 */
class Table {
  friend class TileGroup;
  friend class TableFactory;

  Table() = delete;
  Table(Table const&) = delete;

 public:

  // Table constructor
  Table(catalog::Schema *schema,
        Backend *backend)
 : database_id(INVALID_ID),
   table_id(INVALID_ID),
   backend(backend),
   schema(schema){
  }

  ~Table() {

    // clean up tile groups
    for(auto tile_group : tile_groups)
      delete tile_group;

    // table owns its backend
    delete backend;

    // clean up schema
    delete schema;
  }

  catalog::Schema *GetSchema() const{
    return schema;
  }

  Backend *GetBackend() const {
    return backend;
  }

  //===--------------------------------------------------------------------===//
  // Operations
  //===--------------------------------------------------------------------===//

  // add a new tile group to table
  oid_t AddTileGroup();

  inline TileGroup *GetTileGroup(id_t tile_group_id) const {
    assert(tile_group_id < tile_groups.size());
    return tile_groups[tile_group_id];
  }

  inline unsigned int NumTileGroups() const {
    return tile_groups.size();
  }

 protected:

  //===--------------------------------------------------------------------===//
  // Data members
  //===--------------------------------------------------------------------===//

  // Catalog information
  id_t database_id;
  id_t table_id;

  // backend
  Backend *backend;

  // table schema
  catalog::Schema *schema;

  // set of tile groups
  std::vector<TileGroup*> tile_groups;

  // TODO need some policy ?
  // number of tuples allocated per tilegroup for this table
  size_t tuples_per_tilegroup = 1000;

  std::mutex table_mutex;
};

//===--------------------------------------------------------------------===//
// Table factory
//===--------------------------------------------------------------------===//

class TableFactory {
 public:
  TableFactory();
  virtual ~TableFactory();

  static Table *GetTable(oid_t database_id,
                         catalog::Schema *schema) {

    // create a new backend
    Backend* backend = new VMBackend();

    Table *table =  new Table(schema, backend);

    table->database_id = database_id;

    return table;
  }

};

} // End storage namespace
} // End nstore namespace


