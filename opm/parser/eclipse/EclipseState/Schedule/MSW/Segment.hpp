/*
  Copyright 2015 SINTEF ICT, Applied Mathematics.

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

#ifndef SEGMENT_HPP_HEADER_INCLUDED
#define SEGMENT_HPP_HEADER_INCLUDED

#include <memory>
#include <vector>

namespace Opm {
    class SpiralICD;
    class Valve;

    namespace RestartIO {
        struct RstSegment;
    }
}

namespace Opm {

    class Segment {
    public:

        enum class SegmentType {
            REGULAR,
            SICD,
            AICD, // Not really supported - just included to complete the enum
            VALVE,
        };

        Segment();

        Segment(const Segment& src, double new_depth, double new_length, double new_volume);
        Segment(const Segment& src, double new_depth, double new_length);
        Segment(const Segment& src, double new_volume);
        Segment(int segment_number_in, int branch_in, int outlet_segment_in, double length_in, double depth_in,
                double internal_diameter_in, double roughness_in, double cross_area_in, double volume_in, bool data_ready_in, SegmentType segment_type_in);


        Segment(int segmentNumber,
                int branchNumber,
                int outlegSegment,
                const std::vector<int>& inletSegments,
                double totalLength,
                double depth,
                double internalDiameter,
                double roughness,
                double crossArea,
                double volume,
                bool dataReady,
                SegmentType segmentType,
                std::shared_ptr<SpiralICD> spiralICD,
                std::shared_ptr<Valve> valv);

        Segment(const RestartIO::RstSegment& rst_segment);

        int segmentNumber() const;
        int branchNumber() const;
        int outletSegment() const;
        double totalLength() const;
        double depth() const;
        double internalDiameter() const;
        double roughness() const;
        double crossArea() const;
        double volume() const;
        bool dataReady() const;

        SegmentType segmentType() const;
        int ecl_type_id() const;


        const std::vector<int>& inletSegments() const;

        static double invalidValue();
        static SegmentType type_from_int(int ecl_id);

        bool operator==( const Segment& ) const;
        bool operator!=( const Segment& ) const;

        const std::shared_ptr<SpiralICD>& spiralICD() const;
        const std::shared_ptr<Valve>& getValve() const;
        const Valve* valve() const;

        void updateSpiralICD(const SpiralICD& spiral_icd);
        void updateValve(const Valve& valve, const double segment_length);
        void addInletSegment(const int segment_number);
    private:
        // segment number
        // it should work as a ID.
        int m_segment_number;
        // branch number
        // for top segment, it should always be 1
        int m_branch;
        // the outlet junction segment
        // for top segment, it should be -1
        int m_outlet_segment;
        // the segments whose outlet segments are the current segment
        std::vector<int> m_inlet_segments;
        // length of the segment node to the bhp reference point.
        // when reading in from deck, with 'INC',
        // it will be incremental length before processing.
        // After processing and in the class Well, it always stores the 'ABS' value.
        // which means the total_length
        double m_total_length;
        // depth of the nodes to the bhp reference point
        // when reading in from deck, with 'INC',
        // it will be the incremental depth before processing.
        // in the class Well, it always stores the 'ABS' value.
        // TODO: to check if it is good to use 'ABS' always.
        double m_depth;
        // tubing internal diameter
        // or the equivalent diameter for annular cross-sections
        // for top segment, it is UNDEFINED
        // we use invalid_value for the top segment
        double m_internal_diameter;
        // effective roughness of the tubing
        // used to calculate the Fanning friction factor
        // for top segment, it is UNDEFINED
        // we use invalid_value for the top segment
        double m_roughness;
        // cross-sectional area for fluid flow
        // not defined for the top segment,
        // we use invalid_value for the top segment.
        double m_cross_area;
        // valume of the segment;
        // it is defined for top segment.
        // TODO: to check if the definition is the same with other segments.
        double m_volume;
        // indicate if the data related to 'INC' or 'ABS' is ready
        // the volume will be updated at a final step.
        bool m_data_ready;

        // indicate the type of the segment
        // regular, spiral ICD, or Valve.
        SegmentType m_segment_type;

        // information related to SpiralICD. It is nullptr for segments are not
        // spiral ICD type
        std::shared_ptr<SpiralICD> m_spiral_icd;

        // information related to sub-critical valve. It is nullptr for segments are not
        // of type of Valve
        std::shared_ptr<Valve> m_valve;

        // We are not handling the length of segment projected onto the X-axis and Y-axis.
        // They are not used in the simulations and we are not supporting the plotting.
        // There are other three properties for segment related to thermal conduction,
        // while they are not supported by the keyword at the moment.
    };

    inline bool isRegular(const Segment& segment)
    {
        return segment.segmentType() == Segment::SegmentType::REGULAR;
    }

    inline bool isSpiralICD(const Segment& segment)
    {
        return segment.segmentType() == Segment::SegmentType::SICD;
    }

    inline bool isValve(const Segment& segment)
    {
        return segment.segmentType() == Segment::SegmentType::VALVE;
    }
}

#endif
