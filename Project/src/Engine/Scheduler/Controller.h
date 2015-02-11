#ifndef _SCHEDULER_CONTROLLER_H
#define _SCHEDULER_CONTROLLER_H

#include "../../Common/Base/Handler.h"
#include "../../Common/Base/Queue.h"
#include "../../Common/Base/Singleton.h"

#include "../Objects/Events/AddProperty.h"
#include "../Objects/Events/Remove.h"
#include "../Objects/Events/RemoveProperty.h"

namespace Scheduler {

	class Controller:
		
		public Singleton< Controller >,

		public Handler< Object::AddProperty < KeyboardActionQueue > >,
		public Handler< Object::AddProperty < MouseActionQueue > >,
		public Handler< Object::RemoveProperty < KeyboardActionQueue > >,
		public Handler< Object::RemoveProperty < MouseActionQueue > >,
		public Handler< Object::Remove >,

		public Handler< PushAction< KeyboardAction > >,
		public Handler< PushAction< MouseAction > >,
		public Handler< PopAction< KeyboardAction > >,
		public Handler< PopAction< MouseAction > > {

	private:

		friend class Singleton< Controller >;

		Controller() {
		}

	public:

		void handle( const Object::AddProperty< KeyboardActionQueue > & event );
		void handle( const Object::AddProperty< MouseActionQueue > & event );
		void handle( const Object::RemoveProperty< KeyboardActionQueue > & event );
		void handle( const Object::RemoveProperty< MouseActionQueue > & event );
		void handle( const Object::Remove & event );

		void handle( const PushAction< KeyboardAction > & event );
		void handle( const PushAction< MouseAction > & event );
		void handle( const PopAction< KeyboardAction > & event );
		void handle( const PopAction< MouseAction > & event );
	};
}

#endif
