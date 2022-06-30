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
						"name": "MainWiFiConfigs",
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
						"x": -80,
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
				"component-43": {
					"name": "Label",
					"property": {
						"name": "txt1",
						"parent": "MainWiFiConfigs",
						"hidden": 1,
						"define": 0,
						"alignX": 0,
						"alignY": 0,
						"x": 10,
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
				"component-44": {
					"name": "Object",
					"property": {
						"name": "wifiSSIDBox",
						"parent": "MainWiFiConfigs",
						"hidden": 1,
						"define": 1,
						"alignX": 0,
						"alignY": 0,
						"x": 10,
						"y": 40,
						"width": 300,
						"height": 40,
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
				"component-45": {
					"name": "Label",
					"property": {
						"name": "txt2",
						"parent": "MainWiFiConfigs",
						"hidden": 1,
						"define": 0,
						"alignX": 0,
						"alignY": 0,
						"x": 10,
						"y": 90,
						"width": 0,
						"height": 0,
						"text": "รหัสผ่าน WiFi",
						"text_align": 0,
						"color": "#000000",
						"mode": 0,
						"font": "Kanit_Regular_16"
					}
				},
				"component-46": {
					"name": "Object",
					"property": {
						"name": "wifiPasswordBox",
						"parent": "MainWiFiConfigs",
						"hidden": 1,
						"define": 1,
						"alignX": 0,
						"alignY": 0,
						"x": 10,
						"y": 110,
						"width": 300,
						"height": 40,
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
				"component-47": {
					"name": "Object",
					"property": {
						"name": "MainSensorConfigs",
						"parent": "",
						"hidden": 1,
						"define": 1,
						"alignX": 0,
						"alignY": 0,
						"x": 320,
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
				"component-49": {
					"name": "Label",
					"property": {
						"name": "txtTempSensorLabel",
						"parent": "MainSensorConfigs",
						"hidden": 1,
						"define": 0,
						"alignX": 0,
						"alignY": 0,
						"x": 10,
						"y": 20,
						"width": 0,
						"height": 0,
						"text": "เซ็นเซอร์อุณหภูมิ",
						"text_align": 0,
						"color": "#000000",
						"mode": 0,
						"font": "Kanit_Regular_14"
					}
				},
				"component-50": {
					"name": "Label",
					"property": {
						"name": "txtHumiSensorLabel",
						"parent": "MainSensorConfigs",
						"hidden": 1,
						"define": 0,
						"alignX": 0,
						"alignY": 0,
						"x": 170,
						"y": 20,
						"width": 0,
						"height": 0,
						"text": "เซ็นเซอร์ความชื้นอากาศ",
						"text_align": 0,
						"color": "#000000",
						"mode": 0,
						"font": "Kanit_Regular_14"
					}
				},
				"component-51": {
					"name": "Object",
					"property": {
						"name": "objPosTempSensorSelect",
						"parent": "MainSensorConfigs",
						"hidden": 1,
						"define": 1,
						"alignX": 0,
						"alignY": 0,
						"x": 10,
						"y": 40,
						"width": 140,
						"height": 40,
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
				"component-52": {
					"name": "Object",
					"property": {
						"name": "objPosHumiSensorSelect",
						"parent": "MainSensorConfigs",
						"hidden": 1,
						"define": 1,
						"alignX": 0,
						"alignY": 0,
						"x": 170,
						"y": 40,
						"width": 140,
						"height": 40,
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
				"component-53": {
					"name": "Label",
					"property": {
						"name": "txt3",
						"parent": "MainSensorConfigs",
						"hidden": 1,
						"define": 0,
						"alignX": 0,
						"alignY": 0,
						"x": 10,
						"y": 90,
						"width": 0,
						"height": 0,
						"text": "เซ็นเซอร์ความชื้นดิน",
						"text_align": 0,
						"color": "#000000",
						"mode": 0,
						"font": "Kanit_Regular_14"
					}
				},
				"component-54": {
					"name": "Object",
					"property": {
						"name": "objPosSoilSensorSelect",
						"parent": "MainSensorConfigs",
						"hidden": 1,
						"define": 1,
						"alignX": 0,
						"alignY": 0,
						"x": 10,
						"y": 110,
						"width": 140,
						"height": 40,
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
				"component-55": {
					"name": "Object",
					"property": {
						"name": "objPosLightSensorSelect",
						"parent": "MainSensorConfigs",
						"hidden": 1,
						"define": 1,
						"alignX": 0,
						"alignY": 0,
						"x": 170,
						"y": 110,
						"width": 140,
						"height": 40,
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
				"component-56": {
					"name": "Label",
					"property": {
						"name": "txt4",
						"parent": "MainSensorConfigs",
						"hidden": 1,
						"define": 0,
						"alignX": 0,
						"alignY": 0,
						"x": 170,
						"y": 90,
						"width": 0,
						"height": 0,
						"text": "เซ็นเซอร์แสงสว่าง",
						"text_align": 0,
						"color": "#000000",
						"mode": 0,
						"font": "Kanit_Regular_14"
					}
				},
				"component-58": {
					"name": "Button",
					"property": {
						"name": "btnSettingsWiFi",
						"parent": "topBar",
						"hidden": 1,
						"define": 1,
						"alignX": 0,
						"alignY": 0,
						"x": 170,
						"y": 10,
						"width": 50,
						"height": 40,
						"toggle": 0,
						"text": "",
						"rel_main_color": "#0C8950",
						"rel_grad_color": "#0C8950",
						"pr_main_color": "#0A6E40",
						"pr_grad_color": "#0A6E40",
						"border_width": 0,
						"border_color": "#0B1928",
						"radius": 0,
						"color": "#FFFFFF",
						"font": "Roboto_16",
						"handler": "btnSettingsWiFiHandle"
					}
				},
				"component-59": {
					"name": "Image",
					"property": {
						"name": "img8",
						"parent": "topBar",
						"hidden": 1,
						"define": 0,
						"alignX": 0,
						"alignY": 0,
						"x": 183,
						"y": 19,
						"src": "D:\\GitHub\\Farm1-HandySense-Firmware\\wifi.png",
						"storage": 0
					}
				},
				"component-61": {
					"name": "Button",
					"property": {
						"name": "btnSettingsSensor",
						"parent": "topBar",
						"hidden": 1,
						"define": 1,
						"alignX": 0,
						"alignY": 0,
						"x": 220,
						"y": 10,
						"width": 50,
						"height": 40,
						"toggle": 0,
						"text": "",
						"rel_main_color": "#0EA661",
						"rel_grad_color": "#0EA661",
						"pr_main_color": "#0A6E40",
						"pr_grad_color": "#0A6E40",
						"border_width": 0,
						"border_color": "#0B1928",
						"radius": 0,
						"color": "#FFFFFF",
						"font": "Roboto_16",
						"handler": "btnSettingsSensorHandle"
					}
				},
				"component-62": {
					"name": "Image",
					"property": {
						"name": "img9",
						"parent": "",
						"hidden": 1,
						"define": 0,
						"alignX": 0,
						"alignY": 0,
						"x": 232,
						"y": 20,
						"src": "D:\\GitHub\\Farm1-HandySense-Firmware\\sensor.png",
						"storage": 0
					}
				}
			}
		}
	]
}