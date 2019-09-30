#pragma once
#include"Resource.h"

enum Resource_Type { RESOURCE_NULL = 0, RESOURCE_ANIMATION, RESOURCE_AUDIO, RESOURCE_FONT, RESOURCE_LEVELPOSITIONS, RESOURCE_SPRITE, RESOURCE_TEXTURE };

class Resource_Wrapper {
private:
	Resource* m_resourceContainer;
	Resource_Type m_type;

public:
	Resource_Wrapper();
	Resource_Wrapper(Resource_Type _resType, Resource* _resource);
	Resource_Wrapper(const Resource_Wrapper& _resWrap);
	~Resource_Wrapper();

	void LoadResource(Resource_Type _type, Resource* _resource);

	/*template<typename R>
	R* GetResourceContainer() {
		R* ptr = dynamic_cast<R*>(m_resourceContainer);
		return ptr;
	};*/

	template<typename R>
	R* GetResourceContainer();
};
