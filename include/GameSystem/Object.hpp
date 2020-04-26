#ifndef OBJECT_HPP
#define OBJECT_HPP
#include "GlobalHeader.hpp"
#include <string>
#include <map>
namespace DreamEngine {
	namespace GameSystem
	{
		class Object
		{
		public:
			/*Call the Object class base initialiser and sets the name**/
			Object(const std::string &Name);
			/**Returns whether or not the object is active*/
			bool isActive() const;
			/**Set the object to active or inactive*/
			void SetActive(bool active);
			/**Set the name of the current Object*/
			void SetName(const std::string &name);
			/**Get the name of the current Object*/
			const std::string &GetName() const;

		protected:
			/**Boolean that represents whether or not the Object is active*/
			bool m_Active = false;
			/**String that represents the name of the Object*/
			std::string m_Name;

			virtual void Launch() {};
			virtual void Update() {};
			virtual void FixedUpdate() {};
			virtual void Render() {};


		};

	};
};
#endif