/**
 * Licensed to JumpMind Inc under one or more contributor
 * license agreements.  See the NOTICE file distributed
 * with this work for additional information regarding
 * copyright ownership.  JumpMind Inc licenses this file
 * to you under the GNU General Public License, version 3.0 (GPLv3)
 * (the "License"); you may not use this file except in compliance
 * with the License.
 *
 * You should have received a copy of the GNU General Public License,
 * version 3.0 (GPLv3) along with this library; if not, see
 * <http://www.gnu.org/licenses/>.
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */
#include "model/TriggerHistory.h"

SymStringArray * SymTiggerHistory_getParsedColumnNames(SymTriggerHistory *this) {
    return SymStringArray_split(this->columnNames, ",");
}

SymStringArray * SymTiggerHistory_getParsedPkColumnNames(SymTriggerHistory *this) {
    return SymStringArray_split(this->pkColumnNames, ",");
}

SymList * SymTiggerHistory_getParsedColumns(SymTriggerHistory *this) {
    SymList *columns = SymList_new(NULL);
    SymStringArray *columnNames = this->getParsedColumnNames(this);
    SymStringArray *pkNames = this->getParsedPkColumnNames(this);
    int i;
    unsigned short isPrimaryKey;
    for (i = 0; i < columnNames->size; i++) {
        char *columnName = columnNames->get(columnNames, i);
        isPrimaryKey = pkNames->contains(pkNames, columnName);
        columns->add(columns, SymColumn_new(NULL, columnName, isPrimaryKey));
    }
    columnNames->destroy(columnNames);
    pkNames->destroy(pkNames);
    return columns;
}

void SymTriggerHistory_destroy(SymTriggerHistory *this) {
    free(this);
}

SymTriggerHistory * SymTriggerHistory_new(SymTriggerHistory *this) {
    if (this == NULL) {
        this = (SymTriggerHistory *) calloc(1, sizeof(SymTriggerHistory));
    }
    this->getParsedColumns = (void *) SymTiggerHistory_getParsedColumns;
    this->getParsedColumnNames = (void *) SymTiggerHistory_getParsedColumnNames;
    this->getParsedPkColumnNames = (void *) SymTiggerHistory_getParsedPkColumnNames;
    this->destroy = (void *) &SymTriggerHistory_destroy;
    return this;
}

SymTriggerHistory * SymTriggerHistory_newWithId(SymTriggerHistory *this, int triggerHistoryId) {
    this = SymTriggerHistory_new(this);
    this->triggerHistoryId = triggerHistoryId;
    return this;
}
