//////////////////////////////////////////////////////////////////////////////
//
// Burngine is distributed under the GNU LGPL v3 License
// ====================================================
//
//    Copyright (C) 2014 Dominik David (frischer-hering@gmx.de)
//
//    This library is free software; you can redistribute it and/or
//    modify it under the terms of the GNU Lesser General Public
//    License as published by the Free Software Foundation;
//    version 3.0 of the License
//
//    This library is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//    Lesser General Public License for more details.
//
//    You should have received a copy of the GNU Lesser General Public
//    License along with this library; if not, write to the Free Software
//    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
//    USA
//
//////////////////////////////////////////////////////////////////////////////

#ifndef THREADLOCALPTR_HPP_
#define THREADLOCALPTR_HPP_

#include <Burngine/Export.hpp>
#include <map>
#include <vector>

namespace burn {

	template<class T>
	class BURNGINE_API_EXPORT ThreadLocalPtr {
	public:

		void set(T* pointer);
		T* get();

		void clear();

	private:
		std::vector<std::pair<void*, T*> > m_pointers;    ///< Pointers associated with thread IDs
	};

} /* namespace burn */

// Member function implementations:
#include <Burngine/System/ThreadLocalPtr.cpp>

#endif /* THREADLOCALPTR_HPP_ */
