////////////////////////////////////////////////////////////////////////
// Simple Geometric Library (sglib)
// Copyright (C) 2020   Artemiy Kanshin
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
/////////////////////////////////////////////////////////////////////////

#ifndef _GEXPORTS_H_
#define _GEXPORTS_H_

#ifdef SGL_EXPORT
    #ifdef _WIN32
        #define SGL_API __declspec(dllexport)
    #else
        #define SGL_API __attribute__((visibility("default")))
    #endif
#else //SGL_IMPORT
    #ifdef _WIN32
        #define SGL_API __declspec(dllimport)
    #else
        #define SGL_API
    #endif
#endif //SGL_EXPORT

#endif //_GEXPORTS_H_
