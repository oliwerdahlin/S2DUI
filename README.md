# S2DUI
A simple UI library inspired by dear ImGUI running on [my OpenGL rendering library](https://github.com/oliwerdahlin/S2DGL)

## Features
+ Menus
+ Submenus
+ Buttons
+ Checkboxes
+ Sliders
+ Text Input Boxes
+ Custom texture and font loading

## Example Code
```
	ui.Begin(6996);

		if (ui.ButtonWithTexture(1, texture))
		{
			//play
		}

		static float value = 0;
		static int valueInt = 0;
		ui.sliderFloat("Slider example", &value, -2, 5, texture, {1,1,1,1}, texture);
		ui.sliderInt("Slider example int", &valueInt, -2, 5, texture, {1,1,1,1}, texture);

		glm::vec4 customTransform = {};
		bool clicked = 0;
		bool hovered = 0;
		if (ui.CustomWidget(23, &customTransform, &hovered, &clicked))
		{
			if (clicked)
			{
				renderer.renderRectangle(customTransform, Colors_Blue);
			}
			else if (hovered)
			{
				renderer.renderRectangle(customTransform, Colors_Green);
			}
			else
			{
				renderer.renderRectangle(customTransform, Colors_Red);
			}
		}

		ui.BeginMenu("color test", Colors_Transparent, texture);
		{
			static glm::vec3 color = {};
			static glm::vec3 color2 = {};
			ui.colorPicker("color example", &color[0], texture, texture);
			ui.colorPicker("color example2", &color2[0], texture, texture);

			ui.newColum(0);

			ui.Texture(3, texture, {color, 1});
			ui.Texture(4, texture, {color2, 1});
		
		}
		ui.EndMenu();


		ui.BeginMenu("settings", Colors_Transparent, texture);
			ui.BeginMenu("volume settings", Colors_Transparent, texture);
				static bool sound = true;
				static bool music = true;
				ui.Toggle("sound", Colors_Gray, &sound, texture, tick);
				ui.Toggle("music", Colors_Gray, &music, texture, tick);
			ui.EndMenu();

			ui.BeginMenu("video settings", Colors_Transparent, texture);
				static bool vSync = true;
				static bool shadows = true;
				ui.Toggle("vSync", Colors_Gray, &vSync, texture, tick);
				ui.Toggle("shadows", Colors_Gray, &shadows, texture, tick);
			ui.EndMenu();
		ui.EndMenu();

		ui.BeginMenu("create new world", Colors_Green, texture);
			ui.Text("Enter world name", Colors_Gray);
			static char text[15];
			ui.InputText("input", text, sizeof(text));
			ui.Button("create", Colors_Transparent, texture);
		ui.EndMenu();
		ui.Button("Exit", Colors_Transparent, {});

	ui.End();
```
## Results in this
![S2DUI](https://github.com/oliwerdahlin/S2DUI/assets/45284364/d8f3d353-5871-44bd-b845-1af2dce5c106)
## With submenus like these
![S2DUI1](https://github.com/oliwerdahlin/S2DUI/assets/45284364/23ea8a84-0dfd-43d3-a39d-685f3a19bb3c)
![S2DUI2](https://github.com/oliwerdahlin/S2DUI/assets/45284364/1fbf1913-53d0-4ce2-bf9d-6606484aceb1)
