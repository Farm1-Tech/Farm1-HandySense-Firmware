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
						"name": "Main",
						"parent": "",
						"hidden": 1,
						"define": 0,
						"alignX": 0,
						"alignY": 0,
						"x": 0,
						"y": 0,
						"width": 320,
						"height": 240,
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
				"component-1": {
					"name": "Object",
					"property": {
						"name": "tempBox",
						"parent": "Main",
						"hidden": 1,
						"define": 0,
						"alignX": 0,
						"alignY": 0,
						"x": 10,
						"y": 60,
						"width": 140,
						"height": 80,
						"main_color": "#FFFFFF",
						"grad_color": "#FFFFFF",
						"radius": 20,
						"opacity": 255,
						"border_width": 1,
						"border_color": "#E4E4E4",
						"border_opacity": 255,
						"shadow_width": 0,
						"shadow_color": "#000000",
						"shadow_type": 1
					}
				},
				"component-2": {
					"name": "Label",
					"property": {
						"name": "txt1",
						"parent": "tempBox",
						"hidden": 1,
						"define": 0,
						"alignX": 2,
						"alignY": 2,
						"x": -10,
						"y": -20,
						"width": 0,
						"height": 0,
						"text": "อุณหภูมิ",
						"text_align": 0,
						"color": "#000000",
						"mode": 0,
						"font": "Kanit_Regular_14"
					}
				},
				"component-4": {
					"name": "Label",
					"property": {
						"name": "txtTemp",
						"parent": "tempBox",
						"hidden": 1,
						"define": 1,
						"alignX": 2,
						"alignY": 2,
						"x": -30,
						"y": -37,
						"width": 0,
						"height": 0,
						"text": "20.3",
						"text_align": 0,
						"color": "#000000",
						"mode": 0,
						"font": "Kanit_Regular_20"
					}
				},
				"component-6": {
					"name": "Object",
					"property": {
						"name": "humiBox",
						"parent": "Main",
						"hidden": 1,
						"define": 0,
						"alignX": 0,
						"alignY": 0,
						"x": 170,
						"y": 60,
						"width": 140,
						"height": 80,
						"main_color": "#FFFFFF",
						"grad_color": "#FFFFFF",
						"radius": 20,
						"opacity": 255,
						"border_width": 1,
						"border_color": "#E4E4E4",
						"border_opacity": 255,
						"shadow_width": 0,
						"shadow_color": "#000000",
						"shadow_type": 1
					}
				},
				"component-7": {
					"name": "Object",
					"property": {
						"name": "humi2Box",
						"parent": "Main",
						"hidden": 1,
						"define": 0,
						"alignX": 0,
						"alignY": 0,
						"x": 10,
						"y": 150,
						"width": 140,
						"height": 80,
						"main_color": "#FFFFFF",
						"grad_color": "#FFFFFF",
						"radius": 20,
						"opacity": 255,
						"border_width": 1,
						"border_color": "#E4E4E4",
						"border_opacity": 255,
						"shadow_width": 0,
						"shadow_color": "#D6D6D6",
						"shadow_type": 1
					}
				},
				"component-8": {
					"name": "Object",
					"property": {
						"name": "lightBox",
						"parent": "Main",
						"hidden": 1,
						"define": 0,
						"alignX": 0,
						"alignY": 0,
						"x": 170,
						"y": 150,
						"width": 140,
						"height": 80,
						"main_color": "#FFFFFF",
						"grad_color": "#FFFFFF",
						"radius": 20,
						"opacity": 255,
						"border_width": 1,
						"border_color": "#E4E4E4",
						"border_opacity": 255,
						"shadow_width": 0,
						"shadow_color": "#000000",
						"shadow_type": 1
					}
				},
				"component-10": {
					"name": "Image",
					"property": {
						"name": "img1",
						"parent": "",
						"hidden": 1,
						"define": 0,
						"alignX": 0,
						"alignY": 0,
						"x": 20,
						"y": 80,
						"src": "D:\\GitHub\\Farm1-HandySense-Firmware\\thermometer.png",
						"storage": 0
					}
				},
				"component-11": {
					"name": "Image",
					"property": {
						"name": "img2",
						"parent": "humiBox",
						"hidden": 1,
						"define": 0,
						"alignX": 0,
						"alignY": 0,
						"x": 10,
						"y": 20,
						"src": "D:\\GitHub\\Farm1-HandySense-Firmware\\humidity.png",
						"storage": 0
					}
				},
				"component-12": {
					"name": "Label",
					"property": {
						"name": "txtHumi",
						"parent": "humiBox",
						"hidden": 1,
						"define": 1,
						"alignX": 2,
						"alignY": 2,
						"x": -23,
						"y": -38,
						"width": 0,
						"height": 0,
						"text": "20.3",
						"text_align": 0,
						"color": "#000000",
						"mode": 0,
						"font": "Kanit_Regular_20"
					}
				},
				"component-13": {
					"name": "Label",
					"property": {
						"name": "txt5",
						"parent": "humiBox",
						"hidden": 1,
						"define": 0,
						"alignX": 2,
						"alignY": 2,
						"x": -10,
						"y": -40,
						"width": 0,
						"height": 0,
						"text": "%",
						"text_align": 0,
						"color": "#000000",
						"mode": 0,
						"font": "Kanit_Regular_16"
					}
				},
				"component-14": {
					"name": "Label",
					"property": {
						"name": "txt6",
						"parent": "humiBox",
						"hidden": 1,
						"define": 0,
						"alignX": 2,
						"alignY": 2,
						"x": -10,
						"y": -20,
						"width": 0,
						"height": 0,
						"text": "ความชื้นอากาศ",
						"text_align": 0,
						"color": "#000000",
						"mode": 0,
						"font": "Kanit_Regular_14"
					}
				},
				"component-15": {
					"name": "Label",
					"property": {
						"name": "txt7",
						"parent": "humi2Box",
						"hidden": 1,
						"define": 0,
						"alignX": 2,
						"alignY": 2,
						"x": -10,
						"y": -20,
						"width": 0,
						"height": 0,
						"text": "ความชื้นดิน",
						"text_align": 0,
						"color": "#000000",
						"mode": 0,
						"font": "Kanit_Regular_14"
					}
				},
				"component-16": {
					"name": "Label",
					"property": {
						"name": "txtHumi2",
						"parent": "humi2Box",
						"hidden": 1,
						"define": 1,
						"alignX": 2,
						"alignY": 2,
						"x": -24,
						"y": -38,
						"width": 0,
						"height": 0,
						"text": "20.3",
						"text_align": 0,
						"color": "#000000",
						"mode": 0,
						"font": "Kanit_Regular_20"
					}
				},
				"component-17": {
					"name": "Label",
					"property": {
						"name": "txt9",
						"parent": "humi2Box",
						"hidden": 1,
						"define": 0,
						"alignX": 2,
						"alignY": 2,
						"x": -10,
						"y": -40,
						"width": 0,
						"height": 0,
						"text": "%",
						"text_align": 0,
						"color": "#000000",
						"mode": 0,
						"font": "Kanit_Regular_16"
					}
				},
				"component-18": {
					"name": "Image",
					"property": {
						"name": "img3",
						"parent": "humi2Box",
						"hidden": 1,
						"define": 0,
						"alignX": 0,
						"alignY": 0,
						"x": 10,
						"y": 20,
						"src": "D:\\GitHub\\Farm1-HandySense-Firmware\\humidity2.png",
						"storage": 0
					}
				},
				"component-19": {
					"name": "Label",
					"property": {
						"name": "txtLight",
						"parent": "lightBox",
						"hidden": 1,
						"define": 1,
						"alignX": 2,
						"alignY": 2,
						"x": -47,
						"y": -38,
						"width": 0,
						"height": 0,
						"text": "20.3",
						"text_align": 0,
						"color": "#000000",
						"mode": 0,
						"font": "Kanit_Regular_20"
					}
				},
				"component-21": {
					"name": "Label",
					"property": {
						"name": "txt12",
						"parent": "lightBox",
						"hidden": 1,
						"define": 0,
						"alignX": 2,
						"alignY": 2,
						"x": -10,
						"y": -20,
						"width": 0,
						"height": 0,
						"text": "แสงสว่าง",
						"text_align": 0,
						"color": "#000000",
						"mode": 0,
						"font": "Kanit_Regular_14"
					}
				},
				"component-22": {
					"name": "Label",
					"property": {
						"name": "txt13",
						"parent": "lightBox",
						"hidden": 1,
						"define": 0,
						"alignX": 2,
						"alignY": 2,
						"x": -10,
						"y": -40,
						"width": 0,
						"height": 0,
						"text": "kLux",
						"text_align": 0,
						"color": "#000000",
						"mode": 0,
						"font": "Kanit_Regular_16"
					}
				},
				"component-24": {
					"name": "Image",
					"property": {
						"name": "img4",
						"parent": "lightBox",
						"hidden": 1,
						"define": 0,
						"alignX": 0,
						"alignY": 0,
						"x": 10,
						"y": 20,
						"src": "D:\\GitHub\\Farm1-HandySense-Firmware\\sun.png",
						"storage": 0
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
				"component-29": {
					"name": "Image",
					"property": {
						"name": "imgWiFi",
						"parent": "topBar",
						"hidden": 1,
						"define": 1,
						"alignX": 2,
						"alignY": 1,
						"x": -20,
						"y": 0,
						"src": "D:\\GitHub\\Farm1-HandySense-Firmware\\wifi.png",
						"storage": 0
					}
				},
				"component-30": {
					"name": "Image",
					"property": {
						"name": "imgNexpie",
						"parent": "topBar",
						"hidden": 1,
						"define": 1,
						"alignX": 2,
						"alignY": 1,
						"x": -50,
						"y": 0,
						"src": "D:\\GitHub\\Farm1-HandySense-Firmware\\cloud-computing.png",
						"storage": 0
					}
				},
				"component-31": {
					"name": "Label",
					"property": {
						"name": "txt14",
						"parent": "tempBox",
						"hidden": 1,
						"define": 0,
						"alignX": 2,
						"alignY": 2,
						"x": -10,
						"y": -40,
						"width": 0,
						"height": 0,
						"text": "*C",
						"text_align": 0,
						"color": "#000000",
						"mode": 0,
						"font": "Kanit_Regular_16"
					}
				},
				"component-32": {
					"name": "Label",
					"property": {
						"name": "txtTime",
						"parent": "topBar",
						"hidden": 1,
						"define": 1,
						"alignX": 0,
						"alignY": 1,
						"x": 50,
						"y": 0,
						"width": 0,
						"height": 0,
						"text": "Hello",
						"text_align": 0,
						"color": "#FFFFFF",
						"mode": 0,
						"font": "Kanit_Regular_20"
					}
				},
				"component-35": {
					"name": "Button",
					"property": {
						"name": "btnGoToSettings",
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
						"handler": "btnGoToSettingsHandle"
					}
				},
				"component-37": {
					"name": "Image",
					"property": {
						"name": "img5",
						"parent": "topBar",
						"hidden": 1,
						"define": 0,
						"alignX": 0,
						"alignY": 1,
						"x": 10,
						"y": 0,
						"src": "D:\\GitHub\\Farm1-HandySense-Firmware\\gear.png",
						"storage": 0
					}
				}
			}
		}
	]
}