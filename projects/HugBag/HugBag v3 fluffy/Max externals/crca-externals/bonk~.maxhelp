{
	"patcher" : 	{
		"fileversion" : 1,
		"rect" : [ 0.0, 40.0, 1440.0, 804.0 ],
		"bglocked" : 0,
		"defrect" : [ 0.0, 40.0, 1440.0, 804.0 ],
		"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
		"openinpresentation" : 0,
		"default_fontsize" : 10.0,
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
					"maxclass" : "comment",
					"text" : "by slave2sync",
					"numoutlets" : 0,
					"fontsize" : 9.0,
					"patching_rect" : [ 398.800293, 53.85643, 94.0, 17.0 ],
					"fontname" : "Arial",
					"numinlets" : 1,
					"id" : "obj-77"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Mach-O Windows build 25-2-2011",
					"numoutlets" : 0,
					"fontsize" : 9.0,
					"patching_rect" : [ 186.656708, 53.09808, 207.078888, 17.0 ],
					"fontname" : "Arial",
					"numinlets" : 1,
					"id" : "obj-76"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "read",
					"numoutlets" : 1,
					"fontsize" : 9.0,
					"outlettype" : [ "" ],
					"patching_rect" : [ 303.0, 306.0, 30.0, 15.0 ],
					"fontname" : "Arial",
					"numinlets" : 2,
					"id" : "obj-1"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p documentation",
					"numoutlets" : 0,
					"fontsize" : 9.0,
					"patching_rect" : [ 48.0, 71.0, 80.0, 17.0 ],
					"fontname" : "Arial",
					"numinlets" : 0,
					"id" : "obj-2",
					"color" : [ 0.380392, 0.611765, 0.611765, 1.0 ],
					"patcher" : 					{
						"fileversion" : 1,
						"rect" : [ 8.0, 71.0, 285.0, 514.0 ],
						"bglocked" : 0,
						"defrect" : [ 8.0, 71.0, 285.0, 514.0 ],
						"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
						"openinpresentation" : 0,
						"default_fontsize" : 10.0,
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
						"boxes" : [ 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "Version 1.3 May 2003 - OS X",
									"numoutlets" : 0,
									"fontsize" : 9.0,
									"patching_rect" : [ 26.0, 59.0, 139.0, 17.0 ],
									"fontname" : "Arial",
									"numinlets" : 1,
									"id" : "obj-1"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "an attack detector for small percussion instruments",
									"linecount" : 2,
									"numoutlets" : 0,
									"fontsize" : 9.0,
									"patching_rect" : [ 122.0, 31.0, 133.0, 27.0 ],
									"fontname" : "Arial",
									"numinlets" : 1,
									"id" : "obj-2"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "MSP port by Ted Apel",
									"numoutlets" : 0,
									"fontsize" : 9.0,
									"patching_rect" : [ 26.0, 89.0, 107.0, 17.0 ],
									"fontname" : "Arial",
									"numinlets" : 1,
									"id" : "obj-3"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "by Miller Puckette",
									"numoutlets" : 0,
									"fontsize" : 9.0,
									"patching_rect" : [ 26.0, 74.0, 94.0, 17.0 ],
									"fontname" : "Arial",
									"numinlets" : 1,
									"id" : "obj-4"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "fpic",
									"numoutlets" : 0,
									"patching_rect" : [ 27.0, 31.0, 92.0, 22.0 ],
									"embed" : 1,
									"numinlets" : 1,
									"id" : "obj-5",
									"data" : [ 104, "png", "IBkSG0fBZn....PCIgDQRA...vE...fEHX....PSrruT....DLmPIQEBHf.B7g.YHB...7QRDEDUXUX6AGS.....BCZ8O0FCe.J..........9X.eXK.AXCBlsJ.....IUjSD4pPfIH" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "In this patch, after starting DSP, you can print out the raw or cooked output using the two toggles or listen to the synthesizer output by raising its volume.",
									"linecount" : 3,
									"numoutlets" : 0,
									"fontsize" : 9.0,
									"patching_rect" : [ 26.0, 406.0, 217.0, 38.0 ],
									"fontname" : "Arial",
									"numinlets" : 1,
									"id" : "obj-6"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "Bonk's analysis is carried out on a 256-point window (6 msec at 44.1kHz) and by default the analysis period is 128 samples. The analysis period can be specified as Bonk's creation argument but must be a multiple of 64.",
									"linecount" : 5,
									"numoutlets" : 0,
									"fontsize" : 9.0,
									"patching_rect" : [ 26.0, 340.0, 218.0, 58.0 ],
									"fontname" : "Arial",
									"numinlets" : 1,
									"id" : "obj-7"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "Bonk's two outputs are the raw spectrum of the attack (provided as a list of 11 numbers giving the signal \"loudness\" in the 11 frequency bands used), and the \"cooked\" output which gives only an instrument number (counting up from zero) and a \"velocity\". The instrument number is significant only in that bonk~ has a \"template set\" in memory.",
									"linecount" : 7,
									"numoutlets" : 0,
									"fontsize" : 9.0,
									"patching_rect" : [ 26.0, 239.0, 218.0, 79.0 ],
									"fontname" : "Arial",
									"numinlets" : 1,
									"id" : "obj-8"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "The bonk~ object takes an audio signal input and looks for \"attacks\" defined as sharp changes in the spectral envelope of the incoming sound. Optionally, and less reliably, you can have bonk~ check the attack against a collection of stored templates to try to guess which of two or more instruments was hit. Bonk~ is described theoretically in the 1998 ICMC proceedings, reprinted on http://www.crca.ucsd.edu/~msp.",
									"linecount" : 9,
									"numoutlets" : 0,
									"fontsize" : 9.0,
									"patching_rect" : [ 26.0, 114.0, 219.0, 100.0 ],
									"fontname" : "Arial",
									"numinlets" : 1,
									"id" : "obj-9"
								}

							}
 ],
						"lines" : [  ]
					}
,
					"saved_object_attributes" : 					{
						"fontface" : 0,
						"fontsize" : 10.0,
						"globalpatchername" : "",
						"default_fontname" : "Arial",
						"default_fontsize" : 10.0,
						"fontname" : "Arial",
						"default_fontface" : 0
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Print raw output •",
					"linecount" : 2,
					"numoutlets" : 0,
					"fontsize" : 9.0,
					"patching_rect" : [ 138.0, 428.0, 50.0, 27.0 ],
					"fontname" : "Arial",
					"numinlets" : 1,
					"id" : "obj-3"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "toggle",
					"numoutlets" : 1,
					"outlettype" : [ "int" ],
					"patching_rect" : [ 194.0, 437.0, 15.0, 15.0 ],
					"numinlets" : 1,
					"id" : "obj-4"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "toggle",
					"numoutlets" : 1,
					"outlettype" : [ "int" ],
					"patching_rect" : [ 92.0, 437.0, 15.0, 15.0 ],
					"numinlets" : 1,
					"id" : "obj-5"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : ";\r\ndsp sr 44100",
					"linecount" : 2,
					"numoutlets" : 1,
					"fontsize" : 9.0,
					"outlettype" : [ "" ],
					"patching_rect" : [ 462.0, 382.0, 72.0, 25.0 ],
					"fontname" : "Arial",
					"numinlets" : 2,
					"id" : "obj-6"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "loadbang",
					"numoutlets" : 1,
					"fontsize" : 9.0,
					"outlettype" : [ "bang" ],
					"patching_rect" : [ 462.0, 335.0, 46.0, 17.0 ],
					"hidden" : 1,
					"fontname" : "Arial",
					"numinlets" : 1,
					"id" : "obj-7"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : ";\r\ndsp sigvs 64",
					"linecount" : 2,
					"numoutlets" : 1,
					"fontsize" : 9.0,
					"outlettype" : [ "" ],
					"patching_rect" : [ 462.0, 353.0, 72.0, 25.0 ],
					"fontname" : "Arial",
					"numinlets" : 2,
					"id" : "obj-8"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Signal Vector Size must be set to 64.",
					"linecount" : 2,
					"numoutlets" : 0,
					"fontsize" : 9.0,
					"patching_rect" : [ 537.0, 367.0, 89.0, 27.0 ],
					"fontname" : "Arial",
					"numinlets" : 1,
					"id" : "obj-9"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "80",
					"numoutlets" : 1,
					"fontsize" : 9.0,
					"outlettype" : [ "" ],
					"patching_rect" : [ 324.0, 418.0, 20.0, 15.0 ],
					"fontname" : "Arial",
					"numinlets" : 2,
					"id" : "obj-10"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "0",
					"numoutlets" : 1,
					"fontsize" : 9.0,
					"outlettype" : [ "" ],
					"patching_rect" : [ 308.0, 418.0, 16.0, 15.0 ],
					"fontname" : "Arial",
					"numinlets" : 2,
					"id" : "obj-11"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "number",
					"numoutlets" : 2,
					"triangle" : 0,
					"fontsize" : 9.0,
					"maximum" : 100,
					"outlettype" : [ "int", "bang" ],
					"patching_rect" : [ 308.0, 437.0, 26.0, 17.0 ],
					"htextcolor" : [ 0.870588, 0.870588, 0.870588, 1.0 ],
					"triscale" : 0.9,
					"fontname" : "Arial",
					"bgcolor" : [ 0.866667, 0.866667, 0.866667, 1.0 ],
					"numinlets" : 1,
					"id" : "obj-12",
					"minimum" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p synth",
					"numoutlets" : 0,
					"fontsize" : 9.0,
					"patching_rect" : [ 277.0, 454.0, 41.0, 17.0 ],
					"fontname" : "Arial",
					"numinlets" : 2,
					"id" : "obj-13",
					"patcher" : 					{
						"fileversion" : 1,
						"rect" : [ 463.0, 111.0, 306.0, 494.0 ],
						"bglocked" : 0,
						"defrect" : [ 463.0, 111.0, 306.0, 494.0 ],
						"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
						"openinpresentation" : 0,
						"default_fontsize" : 10.0,
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
						"boxes" : [ 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "*~",
									"numoutlets" : 1,
									"fontsize" : 9.0,
									"outlettype" : [ "signal" ],
									"patching_rect" : [ 46.0, 389.0, 27.0, 17.0 ],
									"fontname" : "Arial",
									"numinlets" : 2,
									"id" : "obj-1"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "number",
									"numoutlets" : 2,
									"fontsize" : 9.0,
									"outlettype" : [ "int", "bang" ],
									"patching_rect" : [ 79.0, 147.0, 29.0, 17.0 ],
									"htextcolor" : [ 0.870588, 0.870588, 0.870588, 1.0 ],
									"triscale" : 0.9,
									"fontname" : "Arial",
									"bgcolor" : [ 0.866667, 0.866667, 0.866667, 1.0 ],
									"numinlets" : 1,
									"id" : "obj-2"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "/ 40.",
									"numoutlets" : 1,
									"fontsize" : 9.0,
									"outlettype" : [ "float" ],
									"patching_rect" : [ 140.0, 247.0, 32.0, 17.0 ],
									"fontname" : "Arial",
									"numinlets" : 2,
									"id" : "obj-3"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "*~",
									"numoutlets" : 1,
									"fontsize" : 9.0,
									"outlettype" : [ "signal" ],
									"patching_rect" : [ 46.0, 350.0, 27.0, 17.0 ],
									"fontname" : "Arial",
									"numinlets" : 2,
									"id" : "obj-4"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "button",
									"numoutlets" : 1,
									"outlettype" : [ "bang" ],
									"patching_rect" : [ 120.0, 272.0, 15.0, 15.0 ],
									"numinlets" : 1,
									"id" : "obj-5"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "$1, 0. 200",
									"numoutlets" : 1,
									"fontsize" : 9.0,
									"outlettype" : [ "" ],
									"patching_rect" : [ 140.0, 294.0, 63.0, 15.0 ],
									"fontname" : "Arial",
									"numinlets" : 2,
									"id" : "obj-6"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "line~",
									"numoutlets" : 2,
									"fontsize" : 9.0,
									"outlettype" : [ "signal", "bang" ],
									"patching_rect" : [ 140.0, 313.0, 30.0, 17.0 ],
									"fontname" : "Arial",
									"numinlets" : 2,
									"id" : "obj-7"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "flonum",
									"numoutlets" : 2,
									"fontsize" : 9.0,
									"outlettype" : [ "float", "bang" ],
									"patching_rect" : [ 46.0, 290.0, 35.0, 17.0 ],
									"htextcolor" : [ 0.870588, 0.870588, 0.870588, 1.0 ],
									"triscale" : 0.9,
									"fontname" : "Arial",
									"bgcolor" : [ 0.866667, 0.866667, 0.866667, 1.0 ],
									"numinlets" : 1,
									"id" : "obj-8"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "mtof",
									"numoutlets" : 1,
									"fontsize" : 9.0,
									"outlettype" : [ "" ],
									"patching_rect" : [ 46.0, 238.0, 29.0, 17.0 ],
									"fontname" : "Arial",
									"numinlets" : 1,
									"id" : "obj-9"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "+ 47",
									"numoutlets" : 1,
									"fontsize" : 9.0,
									"outlettype" : [ "int" ],
									"patching_rect" : [ 46.0, 218.0, 29.0, 17.0 ],
									"fontname" : "Arial",
									"numinlets" : 2,
									"id" : "obj-10"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "/ 7",
									"numoutlets" : 1,
									"fontsize" : 9.0,
									"outlettype" : [ "int" ],
									"patching_rect" : [ 46.0, 198.0, 27.0, 17.0 ],
									"fontname" : "Arial",
									"numinlets" : 2,
									"id" : "obj-11"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "* 12",
									"numoutlets" : 1,
									"fontsize" : 9.0,
									"outlettype" : [ "int" ],
									"patching_rect" : [ 46.0, 178.0, 30.0, 17.0 ],
									"fontname" : "Arial",
									"numinlets" : 2,
									"id" : "obj-12"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "+ 1",
									"numoutlets" : 1,
									"fontsize" : 9.0,
									"outlettype" : [ "int" ],
									"patching_rect" : [ 46.0, 158.0, 27.0, 17.0 ],
									"fontname" : "Arial",
									"numinlets" : 2,
									"id" : "obj-13"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "unpack 0 0 0",
									"numoutlets" : 3,
									"fontsize" : 9.0,
									"outlettype" : [ "int", "int", "int" ],
									"patching_rect" : [ 46.0, 115.0, 65.0, 17.0 ],
									"fontname" : "Arial",
									"numinlets" : 1,
									"id" : "obj-14"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "flonum",
									"numoutlets" : 2,
									"fontsize" : 9.0,
									"outlettype" : [ "float", "bang" ],
									"patching_rect" : [ 140.0, 272.0, 35.0, 17.0 ],
									"htextcolor" : [ 0.870588, 0.870588, 0.870588, 1.0 ],
									"triscale" : 0.9,
									"fontname" : "Arial",
									"bgcolor" : [ 0.866667, 0.866667, 0.866667, 1.0 ],
									"numinlets" : 1,
									"id" : "obj-15"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "/ 100.",
									"numoutlets" : 1,
									"fontsize" : 9.0,
									"outlettype" : [ "float" ],
									"patching_rect" : [ 210.0, 70.0, 44.0, 17.0 ],
									"fontname" : "Arial",
									"numinlets" : 2,
									"id" : "obj-16"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "dac~",
									"numoutlets" : 0,
									"fontsize" : 9.0,
									"patching_rect" : [ 46.0, 417.0, 29.0, 17.0 ],
									"fontname" : "Arial",
									"numinlets" : 2,
									"id" : "obj-17"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "cycle~",
									"numoutlets" : 1,
									"fontsize" : 9.0,
									"outlettype" : [ "signal" ],
									"patching_rect" : [ 46.0, 309.0, 38.0, 17.0 ],
									"fontname" : "Arial",
									"numinlets" : 2,
									"id" : "obj-18"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"numoutlets" : 1,
									"outlettype" : [ "list" ],
									"patching_rect" : [ 46.0, 48.0, 15.0, 15.0 ],
									"numinlets" : 0,
									"id" : "obj-19",
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"numoutlets" : 1,
									"outlettype" : [ "int" ],
									"patching_rect" : [ 210.0, 48.0, 15.0, 15.0 ],
									"numinlets" : 0,
									"id" : "obj-20",
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "inlet volume 0-100",
									"numoutlets" : 0,
									"fontsize" : 9.0,
									"patching_rect" : [ 179.0, 33.0, 91.0, 17.0 ],
									"fontname" : "Arial",
									"numinlets" : 1,
									"id" : "obj-21"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "inlet cooked",
									"numoutlets" : 0,
									"fontsize" : 9.0,
									"patching_rect" : [ 24.0, 31.0, 64.0, 17.0 ],
									"fontname" : "Arial",
									"numinlets" : 1,
									"id" : "obj-22"
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-20", 0 ],
									"destination" : [ "obj-16", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 0 ],
									"destination" : [ "obj-7", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-5", 0 ],
									"destination" : [ "obj-6", 0 ],
									"hidden" : 0,
									"midpoints" : [ 129.0, 289.0, 149.5, 289.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-15", 0 ],
									"destination" : [ "obj-6", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 0 ],
									"destination" : [ "obj-15", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-14", 1 ],
									"destination" : [ "obj-3", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-9", 0 ],
									"destination" : [ "obj-5", 0 ],
									"hidden" : 0,
									"midpoints" : [ 55.5, 263.0, 129.0, 263.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-14", 2 ],
									"destination" : [ "obj-2", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-1", 0 ],
									"destination" : [ "obj-17", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-16", 0 ],
									"destination" : [ "obj-1", 1 ],
									"hidden" : 0,
									"midpoints" : [ 219.5, 374.0, 63.5, 374.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-7", 0 ],
									"destination" : [ "obj-4", 1 ],
									"hidden" : 0,
									"midpoints" : [ 149.5, 338.0, 63.5, 338.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-1", 0 ],
									"destination" : [ "obj-17", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 0 ],
									"destination" : [ "obj-1", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-18", 0 ],
									"destination" : [ "obj-4", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 0 ],
									"destination" : [ "obj-18", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-9", 0 ],
									"destination" : [ "obj-8", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-10", 0 ],
									"destination" : [ "obj-9", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-11", 0 ],
									"destination" : [ "obj-10", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-12", 0 ],
									"destination" : [ "obj-11", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-13", 0 ],
									"destination" : [ "obj-12", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 0 ],
									"destination" : [ "obj-13", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-19", 0 ],
									"destination" : [ "obj-14", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
 ]
					}
,
					"saved_object_attributes" : 					{
						"fontface" : 0,
						"fontsize" : 10.0,
						"globalpatchername" : "",
						"default_fontname" : "Arial",
						"default_fontsize" : 10.0,
						"fontname" : "Arial",
						"default_fontface" : 0
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "toggle",
					"numoutlets" : 1,
					"outlettype" : [ "int" ],
					"patching_rect" : [ 220.0, 78.0, 15.0, 15.0 ],
					"numinlets" : 1,
					"id" : "obj-14"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "gate",
					"numoutlets" : 1,
					"fontsize" : 9.0,
					"outlettype" : [ "" ],
					"patching_rect" : [ 194.0, 454.0, 27.0, 17.0 ],
					"fontname" : "Arial",
					"numinlets" : 2,
					"id" : "obj-15"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "print",
					"numoutlets" : 0,
					"fontsize" : 9.0,
					"patching_rect" : [ 194.0, 474.0, 30.0, 17.0 ],
					"fontname" : "Arial",
					"numinlets" : 1,
					"id" : "obj-16"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "print",
					"numoutlets" : 0,
					"fontsize" : 9.0,
					"patching_rect" : [ 92.0, 474.0, 30.0, 17.0 ],
					"fontname" : "Arial",
					"numinlets" : 1,
					"id" : "obj-17"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "gate",
					"numoutlets" : 1,
					"fontsize" : 9.0,
					"outlettype" : [ "" ],
					"patching_rect" : [ 92.0, 454.0, 27.0, 17.0 ],
					"fontname" : "Arial",
					"numinlets" : 2,
					"id" : "obj-18"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "button",
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"patching_rect" : [ 220.0, 351.0, 15.0, 15.0 ],
					"numinlets" : 1,
					"id" : "obj-19"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "adc~",
					"numoutlets" : 2,
					"fontsize" : 9.0,
					"outlettype" : [ "signal", "signal" ],
					"patching_rect" : [ 171.0, 100.0, 29.0, 17.0 ],
					"fontname" : "Arial",
					"numinlets" : 1,
					"id" : "obj-20",
					"color" : [ 1.0, 0.890196, 0.090196, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "print",
					"numoutlets" : 1,
					"fontsize" : 9.0,
					"outlettype" : [ "" ],
					"patching_rect" : [ 220.0, 327.0, 30.0, 15.0 ],
					"fontname" : "Arial",
					"numinlets" : 2,
					"id" : "obj-21"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "read templates",
					"numoutlets" : 1,
					"fontsize" : 9.0,
					"outlettype" : [ "" ],
					"patching_rect" : [ 220.0, 306.0, 77.0, 15.0 ],
					"fontname" : "Arial",
					"numinlets" : 2,
					"id" : "obj-22"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "write",
					"numoutlets" : 1,
					"fontsize" : 9.0,
					"outlettype" : [ "" ],
					"patching_rect" : [ 220.0, 288.0, 33.0, 15.0 ],
					"fontname" : "Arial",
					"numinlets" : 2,
					"id" : "obj-23"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "forget",
					"numoutlets" : 1,
					"fontsize" : 9.0,
					"outlettype" : [ "" ],
					"patching_rect" : [ 220.0, 261.0, 64.0, 15.0 ],
					"fontname" : "Arial",
					"numinlets" : 2,
					"id" : "obj-24"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "learn 0",
					"numoutlets" : 1,
					"fontsize" : 9.0,
					"outlettype" : [ "" ],
					"patching_rect" : [ 220.0, 242.0, 64.0, 15.0 ],
					"fontname" : "Arial",
					"numinlets" : 2,
					"id" : "obj-25"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "learn 10",
					"numoutlets" : 1,
					"fontsize" : 9.0,
					"outlettype" : [ "" ],
					"patching_rect" : [ 220.0, 222.0, 64.0, 15.0 ],
					"fontname" : "Arial",
					"numinlets" : 2,
					"id" : "obj-26"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "learn 1",
					"numoutlets" : 1,
					"fontsize" : 9.0,
					"outlettype" : [ "" ],
					"patching_rect" : [ 220.0, 203.0, 64.0, 15.0 ],
					"fontname" : "Arial",
					"numinlets" : 2,
					"id" : "obj-27"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "debounce 0.",
					"numoutlets" : 1,
					"fontsize" : 9.0,
					"outlettype" : [ "" ],
					"patching_rect" : [ 220.0, 184.0, 64.0, 15.0 ],
					"fontname" : "Arial",
					"numinlets" : 2,
					"id" : "obj-28"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "mask 4 0.7",
					"numoutlets" : 1,
					"fontsize" : 9.0,
					"outlettype" : [ "" ],
					"patching_rect" : [ 220.0, 145.0, 65.0, 15.0 ],
					"fontname" : "Arial",
					"numinlets" : 2,
					"id" : "obj-29"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "minvel 10",
					"numoutlets" : 1,
					"fontsize" : 9.0,
					"outlettype" : [ "" ],
					"patching_rect" : [ 220.0, 126.0, 65.0, 15.0 ],
					"fontname" : "Arial",
					"numinlets" : 2,
					"id" : "obj-30"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "thresh 6 50",
					"numoutlets" : 1,
					"fontsize" : 9.0,
					"outlettype" : [ "" ],
					"patching_rect" : [ 220.0, 100.0, 65.0, 15.0 ],
					"fontname" : "Arial",
					"numinlets" : 2,
					"id" : "obj-31"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "fpic",
					"numoutlets" : 0,
					"patching_rect" : [ 187.0, 6.0, 92.0, 22.0 ],
					"embed" : 1,
					"numinlets" : 1,
					"id" : "obj-32",
					"data" : [ 104, "png", "IBkSG0fBZn....PCIgDQRA...vE...fEHX....PSrruT....DLmPIQEBHf.B7g.YHB...7QRDEDUXUX6AGS.....BCZ8O0FCe.J..........9X.eXK.AXCBlsJ.....IUjSD4pPfIH" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "by Miller Puckette",
					"numoutlets" : 0,
					"fontsize" : 9.0,
					"patching_rect" : [ 398.0, 34.0, 94.0, 17.0 ],
					"fontname" : "Arial",
					"numinlets" : 1,
					"id" : "obj-33"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "MSP port by Ted Apel",
					"numoutlets" : 0,
					"fontsize" : 9.0,
					"patching_rect" : [ 494.0, 34.0, 107.0, 17.0 ],
					"fontname" : "Arial",
					"numinlets" : 1,
					"id" : "obj-34"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "bonk~",
					"numoutlets" : 2,
					"fontsize" : 9.0,
					"outlettype" : [ "list", "list" ],
					"patching_rect" : [ 199.0, 402.0, 34.0, 17.0 ],
					"fontname" : "Arial",
					"numinlets" : 1,
					"id" : "obj-35",
					"color" : [ 1.0, 0.890196, 0.090196, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "an attack detector for small percussion instruments",
					"numoutlets" : 0,
					"fontsize" : 9.0,
					"patching_rect" : [ 282.0, 16.0, 293.0, 17.0 ],
					"fontname" : "Arial",
					"numinlets" : 1,
					"id" : "obj-36"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Version 1.3 May 2003 - OS X, Mach-O 2007",
					"numoutlets" : 0,
					"fontsize" : 9.0,
					"patching_rect" : [ 186.0, 34.0, 207.0, 17.0 ],
					"fontname" : "Arial",
					"numinlets" : 1,
					"id" : "obj-37"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "• Set low and high thresholds. Signal growth must exceed the high one and then fall to the low one to make an attack.",
					"linecount" : 2,
					"numoutlets" : 0,
					"fontsize" : 9.0,
					"patching_rect" : [ 289.0, 100.0, 321.0, 27.0 ],
					"fontname" : "Arial",
					"numinlets" : 1,
					"id" : "obj-38"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "• Minimum velocity to output (quieter notes are ignored.)",
					"numoutlets" : 0,
					"fontsize" : 9.0,
					"patching_rect" : [ 289.0, 126.0, 276.0, 17.0 ],
					"fontname" : "Arial",
					"numinlets" : 1,
					"id" : "obj-39"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "• Describes how energyin each frequency band masks later energy in the band. Here the masking is total for 4 analysis periods and then drops by 0.7 each period.",
					"linecount" : 3,
					"numoutlets" : 0,
					"fontsize" : 9.0,
					"patching_rect" : [ 289.0, 145.0, 324.0, 38.0 ],
					"fontname" : "Arial",
					"numinlets" : 1,
					"id" : "obj-40"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "• Minimum time (msec) between attacks",
					"numoutlets" : 0,
					"fontsize" : 9.0,
					"patching_rect" : [ 289.0, 184.0, 278.0, 17.0 ],
					"fontname" : "Arial",
					"numinlets" : 1,
					"id" : "obj-41"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "• Forget all templates and start learning new ones. The argument gives the number of times you will hit each instrument (10 recommended.) Turn on the output volume above for audible feedback as you train Bonk.",
					"linecount" : 3,
					"numoutlets" : 0,
					"fontsize" : 9.0,
					"patching_rect" : [ 289.0, 203.0, 333.0, 38.0 ],
					"fontname" : "Arial",
					"numinlets" : 1,
					"id" : "obj-42"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "• \"Learn 0\" exits learn mode.",
					"numoutlets" : 0,
					"fontsize" : 9.0,
					"patching_rect" : [ 289.0, 242.0, 162.0, 17.0 ],
					"fontname" : "Arial",
					"numinlets" : 1,
					"id" : "obj-43"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "• Forget the last template. In Learn mode, use \"forget\" to erase and record over a template.",
					"linecount" : 2,
					"numoutlets" : 0,
					"fontsize" : 9.0,
					"patching_rect" : [ 289.0, 261.0, 326.0, 27.0 ],
					"fontname" : "Arial",
					"numinlets" : 1,
					"id" : "obj-44"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "• Write templates to a file in text-editable format.",
					"numoutlets" : 0,
					"fontsize" : 9.0,
					"patching_rect" : [ 256.0, 288.0, 271.0, 17.0 ],
					"fontname" : "Arial",
					"numinlets" : 1,
					"id" : "obj-45"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "• Read templates from a file.",
					"numoutlets" : 0,
					"fontsize" : 9.0,
					"patching_rect" : [ 339.0, 307.0, 151.0, 17.0 ],
					"fontname" : "Arial",
					"numinlets" : 1,
					"id" : "obj-46"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "• Print out all settings and templates.",
					"numoutlets" : 0,
					"fontsize" : 9.0,
					"patching_rect" : [ 256.0, 327.0, 185.0, 17.0 ],
					"fontname" : "Arial",
					"numinlets" : 1,
					"id" : "obj-47"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "• Poll the current spectrum via \"raw\" outlet, You can set a very high threshold if you don't want attacks mixed in.",
					"linecount" : 4,
					"numoutlets" : 0,
					"fontsize" : 9.0,
					"patching_rect" : [ 256.0, 351.0, 167.0, 48.0 ],
					"fontname" : "Arial",
					"numinlets" : 1,
					"id" : "obj-48"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "• click here to start DSP.",
					"numoutlets" : 0,
					"fontsize" : 9.0,
					"patching_rect" : [ 239.0, 78.0, 127.0, 17.0 ],
					"fontname" : "Arial",
					"numinlets" : 1,
					"id" : "obj-49"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "• Output volume (0-100)",
					"numoutlets" : 0,
					"fontsize" : 9.0,
					"patching_rect" : [ 335.0, 437.0, 123.0, 17.0 ],
					"fontname" : "Arial",
					"numinlets" : 1,
					"id" : "obj-50"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "WARNING",
					"numoutlets" : 0,
					"fontsize" : 9.0,
					"patching_rect" : [ 537.0, 354.0, 52.0, 17.0 ],
					"fontname" : "Arial",
					"numinlets" : 1,
					"id" : "obj-51"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Print cooked output •",
					"linecount" : 2,
					"numoutlets" : 0,
					"fontsize" : 9.0,
					"patching_rect" : [ 20.0, 428.0, 63.0, 27.0 ],
					"fontname" : "Arial",
					"numinlets" : 1,
					"id" : "obj-52"
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"source" : [ "obj-7", 0 ],
					"destination" : [ "obj-6", 0 ],
					"hidden" : 1,
					"midpoints" : [ 471.5, 351.0, 471.5, 351.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-7", 0 ],
					"destination" : [ "obj-8", 0 ],
					"hidden" : 1,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 0 ],
					"destination" : [ "obj-13", 1 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-11", 0 ],
					"destination" : [ "obj-12", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-10", 0 ],
					"destination" : [ "obj-12", 0 ],
					"hidden" : 0,
					"midpoints" : [ 333.5, 435.0, 317.5, 435.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-35", 0 ],
					"destination" : [ "obj-13", 0 ],
					"hidden" : 0,
					"midpoints" : [ 208.5, 428.0, 286.5, 428.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-35", 1 ],
					"destination" : [ "obj-15", 1 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-31", 0 ],
					"destination" : [ "obj-35", 0 ],
					"hidden" : 0,
					"midpoints" : [ 229.5, 118.0, 208.5, 118.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-30", 0 ],
					"destination" : [ "obj-35", 0 ],
					"hidden" : 0,
					"midpoints" : [ 229.5, 142.0, 208.5, 142.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-29", 0 ],
					"destination" : [ "obj-35", 0 ],
					"hidden" : 0,
					"midpoints" : [ 229.5, 164.0, 208.5, 164.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-28", 0 ],
					"destination" : [ "obj-35", 0 ],
					"hidden" : 0,
					"midpoints" : [ 229.5, 201.0, 208.5, 201.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-27", 0 ],
					"destination" : [ "obj-35", 0 ],
					"hidden" : 0,
					"midpoints" : [ 229.5, 220.0, 208.5, 220.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-26", 0 ],
					"destination" : [ "obj-35", 0 ],
					"hidden" : 0,
					"midpoints" : [ 229.5, 239.0, 208.5, 239.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-19", 0 ],
					"destination" : [ "obj-35", 0 ],
					"hidden" : 0,
					"midpoints" : [ 229.0, 374.0, 208.5, 374.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-20", 0 ],
					"destination" : [ "obj-35", 0 ],
					"hidden" : 0,
					"midpoints" : [ 180.5, 385.0, 208.5, 385.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-25", 0 ],
					"destination" : [ "obj-35", 0 ],
					"hidden" : 0,
					"midpoints" : [ 229.5, 259.0, 208.5, 259.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-24", 0 ],
					"destination" : [ "obj-35", 0 ],
					"hidden" : 0,
					"midpoints" : [ 229.5, 278.0, 208.5, 278.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-23", 0 ],
					"destination" : [ "obj-35", 0 ],
					"hidden" : 0,
					"midpoints" : [ 229.5, 304.0, 208.5, 304.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-22", 0 ],
					"destination" : [ "obj-35", 0 ],
					"hidden" : 0,
					"midpoints" : [ 229.5, 324.0, 208.5, 324.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-21", 0 ],
					"destination" : [ "obj-35", 0 ],
					"hidden" : 0,
					"midpoints" : [ 229.5, 347.0, 208.5, 347.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 0 ],
					"destination" : [ "obj-35", 0 ],
					"hidden" : 0,
					"midpoints" : [ 312.5, 324.0, 208.5, 324.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-15", 0 ],
					"destination" : [ "obj-16", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-4", 0 ],
					"destination" : [ "obj-15", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-14", 0 ],
					"destination" : [ "obj-20", 0 ],
					"hidden" : 0,
					"midpoints" : [ 229.0, 96.0, 180.5, 96.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-35", 0 ],
					"destination" : [ "obj-18", 1 ],
					"hidden" : 0,
					"midpoints" : [ 208.5, 425.0, 109.5, 425.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-18", 0 ],
					"destination" : [ "obj-17", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-5", 0 ],
					"destination" : [ "obj-18", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
 ]
	}

}
