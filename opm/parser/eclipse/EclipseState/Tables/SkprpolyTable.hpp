/*
  Copyright (C) 2018 Statoil ASA

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

#ifndef OPM_PARSER_SKPRPOLY_TABLE_HPP
#define OPM_PARSER_SKPRPOLY_TABLE_HPP

#include <opm/parser/eclipse/EclipseState/Tables/PolyInjTable.hpp>
namespace Opm {

    class DeckKeyword;

    class SkprpolyTable : public PolyInjTable {
    public:

        SkprpolyTable() = default;
        SkprpolyTable(const std::vector<double>& throughputs,
                     const std::vector<double>& velocities,
                     int tableNumber,
                     const std::vector<std::vector<double>>& data,
                     double ref_polymer_concentration);
        explicit SkprpolyTable(const DeckKeyword& table);

        double referenceConcentration() const;
        void setReferenceConcentration(double refConcentration);

        const std::vector<std::vector<double>>& getSkinPressures() const;

        bool operator==(const SkprpolyTable& data) const;

    private:
        double m_ref_polymer_concentration;

    };

}

#endif //OPM_PARSER_SKPRPOLY_TABLE_HPP
