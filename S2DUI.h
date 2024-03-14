#pragma once
#include "S2DGL.h"
#include <string>
#include <unordered_map>

namespace S2DUI
{

	void defaultErrorFunc(const char *msg);
	using errorFuncType = decltype(defaultErrorFunc);

	struct RendererUi
	{

		void renderFrame(
			S2DGL::Renderer2D &renderer,
			S2DGL::Font &font,
			glm::ivec2 mousePos,
			bool mouseClick,
			bool mouseHeld,
			bool mouseReleased,
			bool escapeReleased,
			const std::string &typedInput,
			float deltaTime
		);

		bool Button(std::string name,
			const S2DGL::Color4f colors, const S2DGL::Texture texture = {});

		void Texture(int id, S2DGL::Texture t, S2DGL::Color4f colors = {1,1,1,1}, glm::vec4 textureCoords = {0,1,1,0});

		bool ButtonWithTexture(int id, S2DGL::Texture t, S2DGL::Color4f colors = {1,1,1,1}, glm::vec4 textureCoords = {0,1,1,0});

		bool Toggle(std::string name,
			const S2DGL::Color4f colors, bool *toggle, const S2DGL::Texture texture = {}, const S2DGL::Texture overTexture = {});

		//returns true if you should render it, clicked is optional
		bool CustomWidget(int id, glm::vec4 *transform, bool *hovered = 0, bool *clicked = 0);

		void Text(std::string name,
			const S2DGL::Color4f colors);

		void InputText(std::string name,
			char *text, size_t textSizeWithNullChar, S2DGL::Color4f color = {0,0,0,0}, const S2DGL::Texture texture = {});

		void sliderFloat(std::string name, float *value, float min, float max,
			S2DGL::Texture sliderTexture = {}, S2DGL::Color4f sliderColor = {1,1,1,1},
			S2DGL::Texture ballTexture = {}, S2DGL::Color4f ballColor = {1,1,1,1});

		void sliderInt(std::string name, int *value, int min, int max,
			S2DGL::Texture sliderTexture = {}, S2DGL::Color4f sliderColor = {1,1,1,1},
			S2DGL::Texture ballTexture = {}, S2DGL::Color4f ballColor = {1,1,1,1});

		void colorPicker(std::string name, float *color3Component, S2DGL::Texture sliderTexture = {},
			S2DGL::Texture ballTexture = {});

		void newColum(int id);

		void PushId(int id);

		void PopId();

		void BeginMenu(std::string name, const S2DGL::Color4f colors, const S2DGL::Texture texture);
		void EndMenu();

		void Begin(int id);
		void End();

		struct Internal
		{
			struct InputData
			{
				glm::ivec2 mousePos = {};
				bool mouseClick = 0;
				bool mouseHeld = 0;
				bool mouseReleased = 0;
				bool escapeReleased = 0;
			};

			struct Widget
			{
				int type = 0;
				bool justCreated = true;
				bool usedThisFrame = 0;
				InputData lastFrameData = {};
				S2DGL::Color4f colors = Colors_White;
				S2DGL::Color4f colors2 = Colors_White;
				S2DGL::Texture texture = {};
				S2DGL::Texture textureOver = {};
				glm::vec4 textureCoords = {};
				bool returnFromUpdate = 0;
				bool customWidgetUsed = 0;
				void *pointer = 0;
				bool clicked = 0; //todo for all?
				bool hovered = 0;
				float min = 0;
				float max = 0;
				int minInt = 0;
				int maxInt = 0;
				glm::vec4 returnTransform = {};//todo mabe for every widget?

				struct PersistentData
				{
					bool sliderBeingDragged = 0;
					bool sliderBeingDragged2 = 0;
					bool sliderBeingDragged3 = 0;
				}pd;

				size_t textSize = 0;
			};
			

			std::vector<std::pair<std::string, Widget>> widgetsVector;

			std::unordered_map<std::string, Widget> widgets;

			std::unordered_map<int, std::vector<std::string>> allMenuStacks;

			std::string idStr;
		}internal;

	};

	class Frame
	{
		int lastW;
		int lastH;
		int lastX;
		int lastY;

		bool loaded = 0;

	public:

		Frame(const Frame &other) = delete;
		Frame(const Frame &&other) = delete;
		Frame(glm::ivec4 size);
		~Frame();
	};

	struct Box
	{
		glm::ivec4 dimensions = {};

		float aspect = 0;

		//-1 left
		// 0 none
		// 1 center
		// 2 right
		char XcenterState = 0;
		char YcenterState = 0;

		// 0 pixelSize
		// 1 xDominant
		// 2 yDominant
		char dimensionsState;

		//todo left percent
		Box &xDistancePixels(int dist);
		Box &yDistancePixels(int dist);
		Box &xCenter(int dist = 0);
		Box &yCenter(int dist = 0);
		Box &xLeft(int dist = 0);
		Box &xLeftPerc(float perc = 0);
		Box &yTop(int dist = 0);
		Box &yTopPerc(float perc = 0);
		Box &xRight(int dist = 0);
		Box &yBottom(int dist = 0);

		Box &xDimensionPixels(int dim);
		Box &yDimensionPixels(int dim);

		Box &xDimensionPercentage(float p);
		Box &yDimensionPercentage(float p);

		Box &xAspectRatio(float r);
		Box &yAspectRatio(float r);

		glm::ivec4 operator()();

		operator glm::vec4() { return (*this)(); }
	};

	bool isInButton(const glm::vec2 &p, const glm::vec4 &box);

};