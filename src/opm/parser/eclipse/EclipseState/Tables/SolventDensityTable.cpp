/*
  Copyright (C) 2019 by Norce

  This file is part of the Open Porous Media project (OPM).

  OPM is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  OPM is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with OPM.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <vector>
#include <opm/parser/eclipse/Deck/DeckItem.hpp>
#include <opm/parser/eclipse/Deck/DeckKeyword.hpp>
#include <opm/parser/eclipse/Deck/DeckRecord.hpp>
#include <opm/parser/eclipse/EclipseState/Tables/SolventDensityTable.hpp>

namespace Opm {

        SolventDensityTable::SolventDensityTable()
        {
        }

        SolventDensityTable::SolventDensityTable(const std::vector<double>& tableValues)
            : m_tableValues(tableValues)
        {
        }

        void SolventDensityTable::init(const Opm::DeckRecord& record )
        {
            m_tableValues = record.getItem("SOLVENT_DENSITY").getSIDoubleData();
        }

        const std::vector<double>& SolventDensityTable::getSolventDensityColumn() const
        {
            return m_tableValues;
        }

        bool SolventDensityTable::operator==(const SolventDensityTable& data) const
        {
            return m_tableValues == data.m_tableValues;
        }


}
