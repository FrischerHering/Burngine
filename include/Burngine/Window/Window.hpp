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

#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <Burngine/Export.hpp>
#include <Burngine/System/NonCopyable.hpp>
#include <Burngine/Window/Event.hpp>
#include <Burngine/Window/VideoMode.hpp>
#include <Burngine/Window/WindowHandle.hpp>
#include <Burngine/System/Math.hpp>
#include <Burngine/Window/GlEntity.hpp>
#include <Burngine/System/Clock.hpp>
#include <Burngine/Graphics/RenderTarget.hpp>

#include <string>

namespace burn {

	namespace priv {
		class WindowImpl;
		class GlContext;
	}

	/**
	 * @brief Renderable window. Used to draw graphics in it.
	 */
	class BURNGINE_API_EXPORT Window : public NonCopyable, public RenderTarget {
	public:

		/**
		 * @brief Symbols defining window styles
		 */
		enum Style {
			NORMAL = 0,    ///< Usual window, resizable
			FIXED_SIZE    ///< Window not resizable nor maximizable
		};

	public:

		/**
		 * @brief Default constructor.
		 * Sets some attributes to default values.
		 */
		Window();

		/**
		 * @brief Default destructor.
		 * Closes window and cleans up.
		 */
		~Window();

		/**
		 * @brief Create a window.
		 *
		 * @param videoMode Window's video mode
		 * @param title Window's title (seen in titlebar)
		 *
		 * @return True on success
		 *
		 * @note If created it closes the previous window
		 */
		bool create(const VideoMode& videoMode,
					const std::string& title,
					const Style& style = NORMAL,
					bool fullscreen = false);

		/**
		 * @brief Create a window.
		 * Uses class' attributes for window creation.
		 * This window will be windowed mode.
		 *
		 * @return True on success
		 *
		 * @note If created it closes the previous window
		 */
		bool create();

		/**
		 * @brief Close the window
		 */
		void close();

		/**
		 * @brief Is the window open?
		 *
		 * @return True if window is open
		 *
		 * @note This has nothing to do with visibility or focus
		 */
		bool isOpen() const;

		/**
		 * @brief Get latest event and remove it from queue
		 *
		 * @param event Latest event will be assigned to this
		 *
		 * @return True if there was an event
		 *
		 * @note This function has to be called! Otherwise the
		 * window will be stuck and not react on anything
		 */
		bool pollEvent(Event& event);

		/**
		 * @brief Clear the displayed window content
		 *
		 * @param color The color with which to clear the screen
		 */
		void clear(const Vector4f& color = Vector4f(0.f));

		/**
		 * @brief Swaps the buffers and thus displays the rendered
		 * content
		 */
		void display();

		/**
		 * @brief Set new video mode and apply it
		 *
		 * @param videoMode New video mode to apply
		 */
		void setVideoMode(const VideoMode& videoMode);

		/**
		 * @brief Get the currently used video mode
		 *
		 * @return Currently used video mode
		 */
		const VideoMode& getVideoMode() const;

		/**
		 * @brief Set new title and apply it
		 *
		 * @param title New title to apply
		 */
		void setTitle(const std::string& title);

		/**
		 * @brief Get the currently set title
		 *
		 * @return Currently set title
		 */
		const std::string& getTitle() const;

		/**
		 * @brief Get the set style of the window
		 *
		 * @return The set style
		 *
		 * @note Styles can be applied only at window creation!
		 */
		const Style& getStyle() const;

		/**
		 * @brief Limit framerate of the window. 0 means "unlimited"
		 *
		 * @param framerate The limit for the framerate or zero for unlimited
		 */
		void setFramerateLimit(const Uint32& framerate);

		/**
		 * @brief Get current framerate limit. zero means unlimited
		 *
		 * @return current framerate limit. zero means unlimited
		 */
		const Uint32& getFramerateLimit() const;

		/**
		 * @brief Used internally. Returns the platform specific
		 * window handle
		 *
		 * @return Platform specific window handle
		 */
		WindowHandle getWindowHandle() const;

		/**
		 * @brief Implementation of RenderTarget's prepare()
		 */
		virtual bool prepare() const;

		/**
		 * @brief Implementation of RenderTarget's getOrtho()
		 */
		virtual Matrix4f getOrtho() const;

		virtual const Vector2ui& getDimensions() const;

	private:
		priv::WindowImpl* m_impl;    ///< Platform-specific window implementation
		VideoMode m_videoMode;    ///< Window's video mode
		std::string m_title;    ///< Window title (seen in titlebar)
		Style m_style;    ///< Window style
		priv::GlContext* m_context;    ///< OpenGL context
		Uint32 m_framerateLimit;    ///< Framerate limit. 0 = unlimited
		Clock m_clock;    ///< Clock for measuring frametime
	};

} /* namespace burn */

#endif /* WINDOW_HPP_ */
