{
	"patcher" : 	{
		"fileversion" : 1,
		"appversion" : 		{
			"major" : 5,
			"minor" : 1,
			"revision" : 9
		}
,
		"rect" : [ 424.0, 104.0, 928.0, 563.0 ],
		"bglocked" : 0,
		"defrect" : [ 424.0, 104.0, 928.0, 563.0 ],
		"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
		"openinpresentation" : 0,
		"default_fontsize" : 12.0,
		"default_fontface" : 0,
		"default_fontname" : "Arial",
		"gridonopen" : 0,
		"gridsize" : [ 15.0, 15.0 ],
		"gridsnaponopen" : 0,
		"toolbarvisible" : 1,
		"boxanimatetime" : 200,
		"imprint" : 0,
		"enablehscroll" : 1,
		"enablevscroll" : 1,
		"devicewidth" : 0.0,
		"boxes" : [ 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "minimum 127",
					"fontsize" : 12.0,
					"id" : "obj-60",
					"numinlets" : 2,
					"numoutlets" : 2,
					"fontname" : "Arial",
					"patching_rect" : [ 408.0, 336.0, 83.0, 20.0 ],
					"outlettype" : [ "int", "int" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "minimum 127",
					"fontsize" : 12.0,
					"id" : "obj-57",
					"numinlets" : 2,
					"numoutlets" : 2,
					"fontname" : "Arial",
					"patching_rect" : [ 699.0, 335.0, 83.0, 20.0 ],
					"outlettype" : [ "int", "int" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "* 0",
					"fontsize" : 12.0,
					"id" : "obj-52",
					"numinlets" : 2,
					"numoutlets" : 1,
					"fontname" : "Arial",
					"patching_rect" : [ 577.0, 336.0, 32.5, 20.0 ],
					"outlettype" : [ "int" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "smoother",
					"fontsize" : 12.0,
					"id" : "obj-3",
					"numinlets" : 1,
					"numoutlets" : 1,
					"fontname" : "Arial",
					"patching_rect" : [ 408.0, 370.0, 61.0, 20.0 ],
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "smoother",
					"fontsize" : 12.0,
					"id" : "obj-2",
					"numinlets" : 1,
					"numoutlets" : 1,
					"fontname" : "Arial",
					"patching_rect" : [ 699.0, 373.0, 61.0, 20.0 ],
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "button",
					"id" : "obj-58",
					"numinlets" : 1,
					"numoutlets" : 1,
					"patching_rect" : [ 15.0, 15.0, 20.0, 20.0 ],
					"outlettype" : [ "bang" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "radius",
					"fontsize" : 9.0,
					"id" : "obj-56",
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 451.0, 402.0, 36.0, 17.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "flonum",
					"fontsize" : 12.0,
					"id" : "obj-50",
					"numinlets" : 1,
					"numoutlets" : 2,
					"fontname" : "Arial",
					"patching_rect" : [ 531.0, 223.0, 42.0, 20.0 ],
					"outlettype" : [ "float", "bang" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "flonum",
					"fontsize" : 12.0,
					"id" : "obj-48",
					"numinlets" : 1,
					"numoutlets" : 2,
					"fontname" : "Arial",
					"patching_rect" : [ 476.0, 223.0, 38.0, 20.0 ],
					"outlettype" : [ "float", "bang" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "* 127.",
					"fontsize" : 9.0,
					"id" : "obj-47",
					"numinlets" : 2,
					"numoutlets" : 1,
					"fontname" : "Arial",
					"patching_rect" : [ 698.0, 253.0, 33.0, 17.0 ],
					"outlettype" : [ "float" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "ctlout 2 1",
					"fontsize" : 12.0,
					"id" : "obj-45",
					"numinlets" : 3,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 512.0, 439.0, 59.0, 20.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "expr \"sqrt(pow($f1-0.5, 2)+pow($f2-0.5, 2)) * 2\"",
					"fontsize" : 12.0,
					"id" : "obj-44",
					"numinlets" : 2,
					"numoutlets" : 1,
					"fontname" : "Arial",
					"patching_rect" : [ 408.0, 281.0, 260.0, 20.0 ],
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "ctlout 1 1",
					"fontsize" : 12.0,
					"id" : "obj-43",
					"numinlets" : 3,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 600.0, 441.0, 59.0, 20.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "number",
					"triscale" : 0.9,
					"fontsize" : 9.0,
					"htextcolor" : [ 0.870588, 0.870588, 0.870588, 1.0 ],
					"id" : "obj-33",
					"numinlets" : 1,
					"numoutlets" : 2,
					"fontname" : "Arial",
					"patching_rect" : [ 408.0, 223.0, 35.0, 17.0 ],
					"outlettype" : [ "int", "bang" ],
					"bgcolor" : [ 0.866667, 0.866667, 0.866667, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "id",
					"fontsize" : 9.0,
					"id" : "obj-53",
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 408.0, 249.0, 34.0, 17.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "perim",
					"fontsize" : 9.0,
					"id" : "obj-42",
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 757.0, 403.0, 32.0, 17.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "dy",
					"fontsize" : 9.0,
					"id" : "obj-41",
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 649.0, 249.0, 32.0, 17.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "dx",
					"fontsize" : 9.0,
					"id" : "obj-40",
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 595.0, 249.0, 32.0, 17.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "number",
					"triscale" : 0.9,
					"fontsize" : 9.0,
					"htextcolor" : [ 0.870588, 0.870588, 0.870588, 1.0 ],
					"id" : "obj-39",
					"minimum" : 0,
					"numinlets" : 1,
					"maximum" : 127,
					"numoutlets" : 2,
					"fontname" : "Arial",
					"patching_rect" : [ 698.0, 402.0, 48.0, 17.0 ],
					"outlettype" : [ "int", "bang" ],
					"bgcolor" : [ 0.866667, 0.866667, 0.866667, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "number",
					"triscale" : 0.9,
					"fontsize" : 9.0,
					"htextcolor" : [ 0.870588, 0.870588, 0.870588, 1.0 ],
					"id" : "obj-38",
					"numinlets" : 1,
					"numoutlets" : 2,
					"fontname" : "Arial",
					"patching_rect" : [ 645.0, 223.0, 35.0, 17.0 ],
					"outlettype" : [ "int", "bang" ],
					"bgcolor" : [ 0.866667, 0.866667, 0.866667, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "number",
					"triscale" : 0.9,
					"fontsize" : 9.0,
					"htextcolor" : [ 0.870588, 0.870588, 0.870588, 1.0 ],
					"id" : "obj-37",
					"numinlets" : 1,
					"numoutlets" : 2,
					"fontname" : "Arial",
					"patching_rect" : [ 595.0, 223.0, 35.0, 17.0 ],
					"outlettype" : [ "int", "bang" ],
					"bgcolor" : [ 0.866667, 0.866667, 0.866667, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "/ 1120.",
					"fontsize" : 9.0,
					"id" : "obj-36",
					"numinlets" : 2,
					"numoutlets" : 1,
					"fontname" : "Arial",
					"patching_rect" : [ 698.0, 225.0, 37.0, 17.0 ],
					"outlettype" : [ "float" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "number",
					"triscale" : 0.9,
					"fontsize" : 9.0,
					"htextcolor" : [ 0.870588, 0.870588, 0.870588, 1.0 ],
					"id" : "obj-1",
					"numinlets" : 1,
					"numoutlets" : 2,
					"fontname" : "Arial",
					"patching_rect" : [ 408.0, 402.0, 35.0, 17.0 ],
					"outlettype" : [ "int", "bang" ],
					"bgcolor" : [ 0.866667, 0.866667, 0.866667, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "* 127.",
					"fontsize" : 9.0,
					"id" : "obj-4",
					"numinlets" : 2,
					"numoutlets" : 1,
					"fontname" : "Arial",
					"patching_rect" : [ 408.0, 311.0, 34.0, 17.0 ],
					"outlettype" : [ "float" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "unpack 1 2 3. 4. 5. 6. 7.",
					"fontsize" : 9.0,
					"id" : "obj-5",
					"numinlets" : 1,
					"numoutlets" : 7,
					"fontname" : "Arial",
					"patching_rect" : [ 503.0, 158.0, 105.0, 17.0 ],
					"outlettype" : [ "int", "int", "float", "float", "float", "float", "float" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "print removeCursor",
					"fontsize" : 9.0,
					"id" : "obj-6",
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 404.0, 192.0, 89.0, 17.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "unpack 1 2",
					"fontsize" : 9.0,
					"id" : "obj-7",
					"numinlets" : 1,
					"numoutlets" : 2,
					"fontname" : "Arial",
					"patching_rect" : [ 403.0, 157.0, 54.0, 17.0 ],
					"outlettype" : [ "int", "int" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "print addCursor",
					"fontsize" : 9.0,
					"id" : "obj-8",
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 330.0, 191.0, 72.0, 17.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "unpack 1 2",
					"fontsize" : 9.0,
					"id" : "obj-9",
					"numinlets" : 1,
					"numoutlets" : 2,
					"fontname" : "Arial",
					"patching_rect" : [ 330.0, 154.0, 54.0, 17.0 ],
					"outlettype" : [ "int", "int" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "route addCursor removeCursor updateCursor",
					"fontsize" : 9.0,
					"id" : "obj-10",
					"numinlets" : 1,
					"numoutlets" : 4,
					"fontname" : "Arial",
					"patching_rect" : [ 330.0, 127.0, 197.0, 17.0 ],
					"outlettype" : [ "", "", "", "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "x-axis",
					"fontsize" : 9.0,
					"id" : "obj-11",
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 477.0, 249.0, 34.0, 17.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "y-axis",
					"fontsize" : 9.0,
					"id" : "obj-12",
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 536.0, 249.0, 32.0, 17.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "number",
					"triscale" : 0.9,
					"fontsize" : 9.0,
					"htextcolor" : [ 0.870588, 0.870588, 0.870588, 1.0 ],
					"id" : "obj-13",
					"numinlets" : 1,
					"numoutlets" : 2,
					"fontname" : "Arial",
					"patching_rect" : [ 185.0, 242.0, 35.0, 17.0 ],
					"outlettype" : [ "int", "bang" ],
					"bgcolor" : [ 0.866667, 0.866667, 0.866667, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "number",
					"triscale" : 0.9,
					"fontsize" : 9.0,
					"htextcolor" : [ 0.870588, 0.870588, 0.870588, 1.0 ],
					"id" : "obj-14",
					"numinlets" : 1,
					"numoutlets" : 2,
					"fontname" : "Arial",
					"patching_rect" : [ 267.0, 243.0, 35.0, 17.0 ],
					"outlettype" : [ "int", "bang" ],
					"bgcolor" : [ 0.866667, 0.866667, 0.866667, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "number",
					"triscale" : 0.9,
					"fontsize" : 9.0,
					"htextcolor" : [ 0.870588, 0.870588, 0.870588, 1.0 ],
					"id" : "obj-15",
					"numinlets" : 1,
					"numoutlets" : 2,
					"fontname" : "Arial",
					"patching_rect" : [ 224.0, 243.0, 35.0, 17.0 ],
					"outlettype" : [ "int", "bang" ],
					"bgcolor" : [ 0.866667, 0.866667, 0.866667, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "* 360.",
					"fontsize" : 9.0,
					"id" : "obj-16",
					"numinlets" : 2,
					"numoutlets" : 1,
					"fontname" : "Arial",
					"patching_rect" : [ 267.0, 211.0, 33.0, 17.0 ],
					"outlettype" : [ "float" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "/ 6.28",
					"fontsize" : 9.0,
					"id" : "obj-17",
					"numinlets" : 2,
					"numoutlets" : 1,
					"fontname" : "Arial",
					"patching_rect" : [ 267.0, 182.0, 32.0, 17.0 ],
					"outlettype" : [ "float" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "* 480.",
					"fontsize" : 9.0,
					"id" : "obj-18",
					"numinlets" : 2,
					"numoutlets" : 1,
					"fontname" : "Arial",
					"patching_rect" : [ 224.0, 210.0, 33.0, 17.0 ],
					"outlettype" : [ "float" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "* 640.",
					"fontsize" : 9.0,
					"id" : "obj-19",
					"numinlets" : 2,
					"numoutlets" : 1,
					"fontname" : "Arial",
					"patching_rect" : [ 186.0, 210.0, 33.0, 17.0 ],
					"outlettype" : [ "float" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "unpack 1 2 3. 4. 5.",
					"fontsize" : 9.0,
					"id" : "obj-20",
					"numinlets" : 1,
					"numoutlets" : 5,
					"fontname" : "Arial",
					"patching_rect" : [ 180.0, 156.0, 87.0, 17.0 ],
					"outlettype" : [ "int", "int", "float", "float", "float" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "print removeObject",
					"fontsize" : 9.0,
					"id" : "obj-21",
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 113.0, 189.0, 88.0, 17.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "unpack 1 2",
					"fontsize" : 9.0,
					"id" : "obj-22",
					"numinlets" : 1,
					"numoutlets" : 2,
					"fontname" : "Arial",
					"patching_rect" : [ 113.0, 157.0, 54.0, 17.0 ],
					"outlettype" : [ "int", "int" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "print addObject",
					"fontsize" : 9.0,
					"id" : "obj-23",
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 40.0, 191.0, 71.0, 17.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "unpack 1 2",
					"fontsize" : 9.0,
					"id" : "obj-24",
					"numinlets" : 1,
					"numoutlets" : 2,
					"fontname" : "Arial",
					"patching_rect" : [ 40.0, 154.0, 54.0, 17.0 ],
					"outlettype" : [ "int", "int" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "route addObject removeObject updateObject",
					"fontsize" : 9.0,
					"id" : "obj-25",
					"numinlets" : 1,
					"numoutlets" : 4,
					"fontname" : "Arial",
					"patching_rect" : [ 40.0, 125.0, 194.0, 17.0 ],
					"outlettype" : [ "", "", "", "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "button",
					"id" : "obj-26",
					"numinlets" : 1,
					"numoutlets" : 1,
					"patching_rect" : [ 79.0, 101.0, 15.0, 15.0 ],
					"outlettype" : [ "bang" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "TuioClient",
					"fontsize" : 9.0,
					"id" : "obj-27",
					"numinlets" : 1,
					"numoutlets" : 2,
					"fontname" : "Arial",
					"patching_rect" : [ 40.0, 49.0, 49.0, 17.0 ],
					"outlettype" : [ "list", "bang" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "simple example patch showing how to receive and unpack the incoming TUIO messages",
					"linecount" : 2,
					"fontsize" : 9.0,
					"id" : "obj-28",
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 204.0, 38.0, 243.0, 27.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "see the help patch for the TuioClient for more info",
					"fontsize" : 9.0,
					"id" : "obj-29",
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 205.0, 70.0, 241.0, 17.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "x-axis",
					"fontsize" : 9.0,
					"id" : "obj-30",
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 184.0, 268.0, 34.0, 17.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "y-axis",
					"fontsize" : 9.0,
					"id" : "obj-31",
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 225.0, 268.0, 32.0, 17.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "angle",
					"fontsize" : 9.0,
					"id" : "obj-32",
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontname" : "Arial",
					"patching_rect" : [ 269.0, 268.0, 32.0, 17.0 ]
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"source" : [ "obj-47", 0 ],
					"destination" : [ "obj-57", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-5", 5 ],
					"destination" : [ "obj-38", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-5", 4 ],
					"destination" : [ "obj-37", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-5", 3 ],
					"destination" : [ "obj-50", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-5", 1 ],
					"destination" : [ "obj-33", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-5", 2 ],
					"destination" : [ "obj-48", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-5", 6 ],
					"destination" : [ "obj-36", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-36", 0 ],
					"destination" : [ "obj-47", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-10", 2 ],
					"destination" : [ "obj-5", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-7", 1 ],
					"destination" : [ "obj-6", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-10", 1 ],
					"destination" : [ "obj-7", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-9", 1 ],
					"destination" : [ "obj-8", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-10", 0 ],
					"destination" : [ "obj-9", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-27", 0 ],
					"destination" : [ "obj-10", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 0 ],
					"destination" : [ "obj-14", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-17", 0 ],
					"destination" : [ "obj-16", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-20", 4 ],
					"destination" : [ "obj-17", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-18", 0 ],
					"destination" : [ "obj-15", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-20", 3 ],
					"destination" : [ "obj-18", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-20", 2 ],
					"destination" : [ "obj-19", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-19", 0 ],
					"destination" : [ "obj-13", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-25", 2 ],
					"destination" : [ "obj-20", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-22", 1 ],
					"destination" : [ "obj-21", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-25", 1 ],
					"destination" : [ "obj-22", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-27", 1 ],
					"destination" : [ "obj-26", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-24", 1 ],
					"destination" : [ "obj-23", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-25", 0 ],
					"destination" : [ "obj-24", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-27", 0 ],
					"destination" : [ "obj-25", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-3", 0 ],
					"destination" : [ "obj-1", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 0 ],
					"destination" : [ "obj-45", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-39", 0 ],
					"destination" : [ "obj-43", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-7", 1 ],
					"destination" : [ "obj-52", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-52", 0 ],
					"destination" : [ "obj-39", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-57", 0 ],
					"destination" : [ "obj-2", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-2", 0 ],
					"destination" : [ "obj-39", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-50", 0 ],
					"destination" : [ "obj-44", 1 ],
					"hidden" : 0,
					"midpoints" : [ 540.5, 243.0, 579.0, 243.0, 579.0, 276.0, 658.5, 276.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-48", 0 ],
					"destination" : [ "obj-44", 0 ],
					"hidden" : 0,
					"midpoints" : [ 485.5, 243.0, 453.0, 243.0, 453.0, 273.0, 417.5, 273.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-44", 0 ],
					"destination" : [ "obj-4", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-4", 0 ],
					"destination" : [ "obj-60", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-60", 0 ],
					"destination" : [ "obj-3", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
 ]
	}

}
