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
						"name": "MainBoxTouchCalibration",
						"parent": "",
						"hidden": 1,
						"define": 1,
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
				"component-58": {
					"name": "Object",
					"property": {
						"name": "objTopLeftTouchPoint",
						"parent": "",
						"hidden": 1,
						"define": 1,
						"alignX": 0,
						"alignY": 0,
						"x": 20,
						"y": 20,
						"width": 16,
						"height": 16,
						"main_color": "#FF0000",
						"grad_color": "#FF0000",
						"radius": 100,
						"opacity": 255,
						"border_width": 0,
						"border_color": "#000000",
						"border_opacity": 255,
						"shadow_width": 0,
						"shadow_color": "#000000",
						"shadow_type": 1
					}
				},
				"component-59": {
					"name": "Label",
					"property": {
						"name": "txt6",
						"parent": "MainBoxTouchCalibration",
						"hidden": 1,
						"define": 0,
						"alignX": 1,
						"alignY": 0,
						"x": 0,
						"y": 20,
						"width": 0,
						"height": 0,
						"text": "ตั้งค่าจุดสัมผัส",
						"text_align": 1,
						"color": "#0EA661",
						"mode": 0,
						"font": "Kanit_Regular_20"
					}
				},
				"component-60": {
					"name": "Object",
					"property": {
						"name": "objBottomLeftTouchPoint",
						"parent": "MainBoxTouchCalibration",
						"hidden": 1,
						"define": 1,
						"alignX": 0,
						"alignY": 2,
						"x": 20,
						"y": -20,
						"width": 16,
						"height": 16,
						"main_color": "#FF0000",
						"grad_color": "#FF0000",
						"radius": 100,
						"opacity": 255,
						"border_width": 0,
						"border_color": "#000000",
						"border_opacity": 255,
						"shadow_width": 0,
						"shadow_color": "#000000",
						"shadow_type": 1
					}
				},
				"component-61": {
					"name": "Object",
					"property": {
						"name": "objBottomRightTouchPoint",
						"parent": "MainBoxTouchCalibration",
						"hidden": 1,
						"define": 1,
						"alignX": 2,
						"alignY": 2,
						"x": -20,
						"y": -20,
						"width": 16,
						"height": 16,
						"main_color": "#FF0000",
						"grad_color": "#FF0000",
						"radius": 100,
						"opacity": 255,
						"border_width": 0,
						"border_color": "#000000",
						"border_opacity": 255,
						"shadow_width": 0,
						"shadow_color": "#000000",
						"shadow_type": 1
					}
				},
				"component-62": {
					"name": "Object",
					"property": {
						"name": "objRightLeftTouchPoint",
						"parent": "MainBoxTouchCalibration",
						"hidden": 1,
						"define": 1,
						"alignX": 2,
						"alignY": 0,
						"x": -20,
						"y": 20,
						"width": 16,
						"height": 16,
						"main_color": "#FF0000",
						"grad_color": "#FF0000",
						"radius": 100,
						"opacity": 255,
						"border_width": 0,
						"border_color": "#000000",
						"border_opacity": 255,
						"shadow_width": 0,
						"shadow_color": "#000000",
						"shadow_type": 1
					}
				},
				"component-63": {
					"name": "Label",
					"property": {
						"name": "txtTouchCalibrationCountdown",
						"parent": "MainBoxTouchCalibration",
						"hidden": 1,
						"define": 1,
						"alignX": 1,
						"alignY": 1,
						"x": 0,
						"y": 26,
						"width": 0,
						"height": 0,
						"text": "เหลืออีก 0 วินาที",
						"text_align": 0,
						"color": "#E74C3C",
						"mode": 0,
						"font": "Kanit_Regular_16"
					}
				},
				"component-64": {
					"name": "Label",
					"property": {
						"name": "txtTouchCalibrationStep",
						"parent": "MainBoxTouchCalibration",
						"hidden": 1,
						"define": 1,
						"alignX": 1,
						"alignY": 1,
						"x": 0,
						"y": 0,
						"width": 0,
						"height": 0,
						"text": "กดจุดด้านบนซ้ายค้างไว้",
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