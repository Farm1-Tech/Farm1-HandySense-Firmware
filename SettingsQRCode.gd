{
	"font": [
		{
			"name": "Roboto_16",
			"size": 16,
			"range": "0x0020-0x007F",
			"variable": "lv_font_roboto_16",
			"file": "font/Roboto-Regular.ttf"
		},
		{
			"name": "Kanit_Regular_20",
			"file": "Kanit_Regular.ttf",
			"size": 20,
			"range": "0x0E00-0x0E7F,0x0020-0x007F"
		},
		{
			"name": "Kanit_Regular_16",
			"file": "Kanit_Regular.ttf",
			"size": 16,
			"range": "0x0E00-0x0E7F,0x0020-0x007F"
		},
		{
			"name": "Kanit_Regular_14",
			"file": "Kanit_Regular.ttf",
			"size": 14,
			"range": "0x0E00-0x0E7F"
		}
	],
	"page": [
		{
			"name": "index",
			"background": {
				"main_color": "#FFFFFF",
				"grad_color": "#FFFFFF"
			},
			"component": {
				"component-0": {
					"name": "Object",
					"property": {
						"name": "MainBoxQRConfigs",
						"parent": "",
						"hidden": 1,
						"define": 1,
						"alignX": 0,
						"alignY": 0,
						"x": 0,
						"y": 50,
						"width": 320,
						"height": 190,
						"main_color": "#f9f9f9",
						"grad_color": "#f9f9f9",
						"radius": 0,
						"opacity": 255,
						"border_width": 0,
						"border_color": "#000000",
						"border_opacity": 255,
						"shadow_width": 0,
						"shadow_color": "#000000",
						"shadow_type": 1
					}
				},
				"component-25": {
					"name": "Object",
					"property": {
						"name": "topBar",
						"parent": "",
						"hidden": 1,
						"define": 0,
						"alignX": 0,
						"alignY": 0,
						"x": 0,
						"y": 0,
						"width": 320,
						"height": 50,
						"main_color": "#0ea661",
						"grad_color": "#0ea661",
						"radius": 0,
						"opacity": 255,
						"border_width": 0,
						"border_color": "#000000",
						"border_opacity": 255,
						"shadow_width": 0,
						"shadow_color": "#000000",
						"shadow_type": 1
					}
				},
				"component-32": {
					"name": "Label",
					"property": {
						"name": "txtHeader",
						"parent": "topBar",
						"hidden": 1,
						"define": 1,
						"alignX": 1,
						"alignY": 1,
						"x": -90,
						"y": 0,
						"width": 0,
						"height": 0,
						"text": "ตั้งค่า",
						"text_align": 0,
						"color": "#FFFFFF",
						"mode": 0,
						"font": "Kanit_Regular_20"
					}
				},
				"component-41": {
					"name": "Button",
					"property": {
						"name": "btn1",
						"parent": "topBar",
						"hidden": 1,
						"define": 0,
						"alignX": 0,
						"alignY": 0,
						"x": 0,
						"y": 0,
						"width": 40,
						"height": 50,
						"toggle": 0,
						"text": "",
						"rel_main_color": "#0EA661",
						"rel_grad_color": "#0EA661",
						"pr_main_color": "#0C8950",
						"pr_grad_color": "#0C8950",
						"border_width": 0,
						"border_color": "#0B1928",
						"radius": 0,
						"color": "#FFFFFF",
						"font": "Roboto_16",
						"handler": "SettingsScreenGoBackHandle"
					}
				},
				"component-42": {
					"name": "Image",
					"property": {
						"name": "img7",
						"parent": "topBar",
						"hidden": 1,
						"define": 0,
						"alignX": 0,
						"alignY": 1,
						"x": 10,
						"y": 0,
						"src": "D:\\GitHub\\Farm1-HandySense-Firmware\\arrow-left.png",
						"storage": 0
					}
				},
				"component-63": {
					"name": "Object",
					"property": {
						"name": "objBoxQRCode",
						"parent": "MainBoxQRConfigs",
						"hidden": 1,
						"define": 0,
						"alignX": 0,
						"alignY": 1,
						"x": 20,
						"y": 0,
						"width": 160,
						"height": 160,
						"main_color": "#000000",
						"grad_color": "#000000",
						"radius": 0,
						"opacity": 255,
						"border_width": 0,
						"border_color": "#000000",
						"border_opacity": 255,
						"shadow_width": 0,
						"shadow_color": "#000000",
						"shadow_type": 1
					}
				},
				"component-64": {
					"name": "Label",
					"property": {
						"name": "txt1",
						"parent": "MainBoxQRConfigs",
						"hidden": 1,
						"define": 0,
						"alignX": 0,
						"alignY": 0,
						"x": 200,
						"y": 20,
						"width": 0,
						"height": 0,
						"text": "ชื่อ WiFi",
						"text_align": 0,
						"color": "#000000",
						"mode": 0,
						"font": "Kanit_Regular_16"
					}
				},
				"component-65": {
					"name": "Object",
					"property": {
						"name": "objBoxWiFiName",
						"parent": "",
						"hidden": 1,
						"define": 0,
						"alignX": 0,
						"alignY": 0,
						"x": 200,
						"y": 90,
						"width": 100,
						"height": 30,
						"main_color": "#FFFFFF",
						"grad_color": "#FFFFFF",
						"radius": 6,
						"opacity": 255,
						"border_width": 2,
						"border_color": "#0EA661",
						"border_opacity": 255,
						"shadow_width": 0,
						"shadow_color": "#000000",
						"shadow_type": 1
					}
				},
				"component-66": {
					"name": "Label",
					"property": {
						"name": "txt2",
						"parent": "MainBoxQRConfigs",
						"hidden": 1,
						"define": 0,
						"alignX": 0,
						"alignY": 0,
						"x": 200,
						"y": 80,
						"width": 0,
						"height": 0,
						"text": "รหัสผ่าน WiFi",
						"text_align": 0,
						"color": "#000000",
						"mode": 0,
						"font": "Kanit_Regular_16"
					}
				},
				"component-67": {
					"name": "Object",
					"property": {
						"name": "objBoxWiFiPassword",
						"parent": "",
						"hidden": 1,
						"define": 0,
						"alignX": 0,
						"alignY": 0,
						"x": 200,
						"y": 150,
						"width": 100,
						"height": 30,
						"main_color": "#FFFFFF",
						"grad_color": "#FFFFFF",
						"radius": 6,
						"opacity": 255,
						"border_width": 2,
						"border_color": "#0EA661",
						"border_opacity": 255,
						"shadow_width": 0,
						"shadow_color": "#000000",
						"shadow_type": 1
					}
				},
				"component-68": {
					"name": "Label",
					"property": {
						"name": "txt3",
						"parent": "MainBoxQRConfigs",
						"hidden": 1,
						"define": 0,
						"alignX": 0,
						"alignY": 0,
						"x": 190,
						"y": 140,
						"width": 120,
						"height": 0,
						"text": "สแกน QR Code เพื่อเชื่อมต่อ",
						"text_align": 1,
						"color": "#FF0000",
						"mode": 1,
						"font": "Kanit_Regular_14"
					}
				},
				"component-70": {
					"name": "Label",
					"property": {
						"name": "txt4",
						"parent": "objBoxWiFiName",
						"hidden": 1,
						"define": 0,
						"alignX": 1,
						"alignY": 1,
						"x": 0,
						"y": 0,
						"width": 0,
						"height": 0,
						"text": "Farm1",
						"text_align": 0,
						"color": "#000000",
						"mode": 0,
						"font": "Kanit_Regular_16"
					}
				},
				"component-71": {
					"name": "Label",
					"property": {
						"name": "txt5",
						"parent": "objBoxWiFiPassword",
						"hidden": 1,
						"define": 0,
						"alignX": 1,
						"alignY": 1,
						"x": 0,
						"y": 0,
						"width": 0,
						"height": 0,
						"text": "123456789",
						"text_align": 0,
						"color": "#000000",
						"mode": 0,
						"font": "Kanit_Regular_16"
					}
				}
			}
		}
	]
}