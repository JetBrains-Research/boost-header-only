#ifndef BOOST_GEOMETRY_PROJECTIONS_WAG3_HPP
#define BOOST_GEOMETRY_PROJECTIONS_WAG3_HPP

// Boost.Geometry - extensions-gis-projections (based on PROJ4)
// This file is automatically generated. DO NOT EDIT.

// Copyright (c) 2008-2015 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// This file is converted from PROJ4, http://trac.osgeo.org/proj
// PROJ4 is originally written by Gerald Evenden (then of the USGS)
// PROJ4 is maintained by Frank Warmerdam
// PROJ4 is converted to Boost.Geometry by Barend Gehrels

// Last updated version of proj: 4.9.1

// Original copyright notice:

// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#include <boost/geometry/extensions/gis/projections/impl/base_static.hpp>
#include <boost/geometry/extensions/gis/projections/impl/base_dynamic.hpp>
#include <boost/geometry/extensions/gis/projections/impl/projects.hpp>
#include <boost/geometry/extensions/gis/projections/impl/factory_entry.hpp>

namespace boost { namespace geometry { namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace wag3
    {

            static const double TWOTHIRD = 0.6666666666666666666667;

            struct par_wag3
            {
                double    C_x;
            };

            // template class, using CRTP to implement forward/inverse
            template <typename Geographic, typename Cartesian, typename Parameters>
            struct base_wag3_spheroid : public base_t_fi<base_wag3_spheroid<Geographic, Cartesian, Parameters>,
                     Geographic, Cartesian, Parameters>
            {

                 typedef double geographic_type;
                 typedef double cartesian_type;

                par_wag3 m_proj_parm;

                inline base_wag3_spheroid(const Parameters& par)
                    : base_t_fi<base_wag3_spheroid<Geographic, Cartesian, Parameters>,
                     Geographic, Cartesian, Parameters>(*this, par) {}

                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(geographic_type& lp_lon, geographic_type& lp_lat, cartesian_type& xy_x, cartesian_type& xy_y) const
                {
                    xy_x = this->m_proj_parm.C_x * lp_lon * cos(TWOTHIRD * lp_lat);
                    xy_y = lp_lat;
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(cartesian_type& xy_x, cartesian_type& xy_y, geographic_type& lp_lon, geographic_type& lp_lat) const
                {
                    lp_lat = xy_y;
                    lp_lon = xy_x / (this->m_proj_parm.C_x * cos(TWOTHIRD * lp_lat));
                }

                static inline std::string get_name()
                {
                    return "wag3_spheroid";
                }

            };

            // Wagner III
            template <typename Parameters>
            void setup_wag3(Parameters& par, par_wag3& proj_parm)
            {
                double ts;

                ts = pj_param(par.params, "rlat_ts").f;
                proj_parm.C_x = cos(ts) / cos(2.*ts/3.);
                par.es = 0.;
            }

        }} // namespace detail::wag3
    #endif // doxygen

    /*!
        \brief Wagner III projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Projection parameters
         - lat_ts: Latitude of true scale (degrees)
        \par Example
        \image html ex_wag3.gif
    */
    template <typename Geographic, typename Cartesian, typename Parameters = parameters>
    struct wag3_spheroid : public detail::wag3::base_wag3_spheroid<Geographic, Cartesian, Parameters>
    {
        inline wag3_spheroid(const Parameters& par) : detail::wag3::base_wag3_spheroid<Geographic, Cartesian, Parameters>(par)
        {
            detail::wag3::setup_wag3(this->m_par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Factory entry(s)
        template <typename Geographic, typename Cartesian, typename Parameters>
        class wag3_entry : public detail::factory_entry<Geographic, Cartesian, Parameters>
        {
            public :
                virtual projection<Geographic, Cartesian>* create_new(const Parameters& par) const
                {
                    return new base_v_fi<wag3_spheroid<Geographic, Cartesian, Parameters>, Geographic, Cartesian, Parameters>(par);
                }
        };

        template <typename Geographic, typename Cartesian, typename Parameters>
        inline void wag3_init(detail::base_factory<Geographic, Cartesian, Parameters>& factory)
        {
            factory.add_to_factory("wag3", new wag3_entry<Geographic, Cartesian, Parameters>);
        }

    } // namespace detail
    #endif // doxygen

}}} // namespace boost::geometry::projections

#endif // BOOST_GEOMETRY_PROJECTIONS_WAG3_HPP

