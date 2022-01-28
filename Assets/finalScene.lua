dim = gr.material({0.8, 0.8, 0.8}, {0.0, 0.0, 0.0}, 1)
purple_mat = gr.material({0.5, 0.0, 0.5}, {0.4, 0.4, 0.4}, 10000)
white = gr.material({1.0, 1.0, 1.0}, {0.1, 0.1, 0.1}, 10)
black = gr.material({0.0, 0.0, 0.0}, {0.1, 0.1, 0.1}, 10)
red = gr.material({1.0, 0.0, 0.0}, {0.1, 0.1, 0.1}, 10)
blue = gr.material({0.29, 0.506, 0.984}, {0.1, 0.1, 0.1}, 10)
yellow = gr.material({0.996, 0.765, 0.047}, {0.1, 0.1, 0.1}, 10)
tan = gr.material({0.836, 0.055, 0.129}, {0.1, 0.1, 0.1}, 10)
brown = gr.material({0.333, 0.029, 0.0}, {0.1, 0.1, 0.1}, 10)
pink = gr.material({0.988, 0.137, 0.729}, {0.1, 0.1, 0.1}, 10)
green = gr.material({0.0, 1.0, 0.5}, {0.1, 0.1, 0.1}, 10)
green2 = gr.material({0.0, 0.9, 0.8}, {0.1, 0.1, 0.1}, 10)
glass = gr.material( {0.5, 0.5, 0.5}, {0.5, 0.7, 0.5},  25, 0.8, 0.0, 0.2)	

scene_root = gr.node('scene_root') 

plane = gr.mesh( 'plane', 'plane.obj' )
scene_root:add_child(plane)
plane:set_material(dim)
plane:scale(30, 30, 30)

body = gr.sphere('sphere')
body:set_material(yellow)
body:scale(0.7, 0.8, 0.5)
body:translate(0.0, 3.0, 0.0)
scene_root:add_child(body)

-- neck
neckNode = gr.node('neckNode')
neckNode:scale(1.0/0.7, 1.0/0.8, 1.0/0.5)
neckNode:translate(0.0, 0.8, 0.0)
body:add_child(neckNode)

neck = gr.sphere('neck')
neck:scale(0.4, 0.15, 0.4)
neck:set_material(white)
neckNode:add_child(neck)

-- head
head = gr.sphere('sphere')
head:set_material(tan)
head:scale(0.65, 0.75, 0.4)
head:translate(0.0, 0.7, 0.0)
neckNode:add_child(head) 

-- face
leftGlasses = gr.sphere('sphere')
leftGlasses:set_material(brown)
leftGlasses:scale(0.36, 0.33, 0.05)
leftGlasses:translate(-0.41, -0.08, 1.0)
head:add_child(leftGlasses) 

rightGlasses = gr.sphere('sphere')
rightGlasses:set_material(brown)
rightGlasses:scale(0.36, 0.33, 0.05)
rightGlasses:translate(0.41, -0.08, 1.0)
head:add_child(rightGlasses) 

leftEye = gr.sphere('sphere')
leftEye:set_material(white)
leftEye:scale(0.29, 0.27, 0.07)
leftEye:translate(-0.41, -0.08, 1.0)
head:add_child(leftEye) 

rightEye = gr.sphere('sphere')
rightEye:set_material(white)
rightEye:scale(0.29, 0.27, 0.07)
rightEye:translate(0.41, -0.08, 1.0)
head:add_child(rightEye) 

leftEyeball = gr.sphere('sphere')
leftEyeball:set_material(black)
leftEyeball:scale(0.065, 0.08, 0.07)
leftEyeball:translate(-0.41, -0.15, 1.05)
head:add_child(leftEyeball) 

rightEyeball = gr.sphere('sphere')
rightEyeball:set_material(black)
rightEyeball:scale(0.065, 0.08, 0.07)
rightEyeball:translate(0.41, -0.15, 1.05)
head:add_child(rightEyeball) 

mouth = gr.sphere('sphere')
mouth:set_material(black)
mouth:scale(1.0/0.65 * 0.1, 1.0/0.75 * 0.08, 1.0/0.6 * 0.01)
mouth:translate(0.0, -0.70, 0.75)
head:add_child(mouth) 

-- left ear
leftEarNode = gr.node('leftEarNode')
leftEarNode:scale(1.0/0.65, 1.0/0.75, 1.0/0.6)
leftEarNode:translate(-0.7, 0.8, 0.0)
head:add_child(leftEarNode)

leftEar = gr.sphere('sphere')
leftEar:scale(0.2, 0.25, 0.08)
leftEar:rotate('z', 30.0)
leftEar:translate(0.0, 0.2, 0.0)
leftEar:set_material(tan)
leftEarNode:add_child(leftEar)

leftInsideEar = gr.sphere('sphere')
leftInsideEar:scale(0.6, 0.65, 0.1)
leftInsideEar:translate(-0.05, -0.22, 0.95)
leftInsideEar:set_material(pink)
leftEar:add_child(leftInsideEar)

-- right ear
rightEarNode = gr.node('rightEarNode')
rightEarNode:scale(1.0/0.65, 1.0/0.75, 1.0/0.6)
rightEarNode:translate(0.7, 0.8, 0.0)
head:add_child(rightEarNode)

rightEar = gr.sphere('sphere')
rightEar:scale(0.2, 0.25, 0.08)
rightEar:rotate('z', -30.0)
rightEar:translate(0.0, 0.2, 0.0)
rightEar:set_material(tan)
rightEarNode:add_child(rightEar)

rightInsideEar = gr.sphere('sphere')
rightInsideEar:scale(0.6, 0.65, 0.1)
rightInsideEar:translate(0.05, -0.22, 0.95)
rightInsideEar:set_material(pink)
rightEar:add_child(rightInsideEar)

-- left arm
leftArmNode = gr.node('leftArmNode')
body:add_child(leftArmNode)
leftArmNode:scale(1.0/0.7, 1.0/0.8, 1.0/0.5)
leftArmNode:translate(-0.8, 0.35, 0.0)

leftArm = gr.sphere('sphere')
leftArm:scale(0.2, 0.4, 0.2)
leftArm:rotate('z', -30.0)
leftArm:translate(-0.1, -0.2, 0.0)
leftArm:set_material(yellow)
leftArmNode:add_child(leftArm)

-- left forearm
leftForearmNode = gr.node('leftForearmNode')
leftForearmNode:scale(1.0/0.2, 1.0/0.4, 1.0/0.2)
leftArm:add_child(leftForearmNode)
leftForearmNode:translate(0.0, -1.1, 0.0)

leftForearm = gr.sphere('sphere')
leftForearm:scale(0.17, 0.35, 0.17)
leftForearm:translate(0.0, -0.2, 0.0)
leftForearm:set_material(yellow)
leftForearmNode:add_child(leftForearm)

-- left hand
leftHandNode = gr.node('leftHandNode')
leftHandNode:scale(1.0/0.17, 1.0/0.35, 1.0/0.17)
leftForearm:add_child(leftHandNode)
leftHandNode:translate(0.0, -1.2, 0.0)

leftHand =gr.sphere('sphere')
leftHand:scale(0.2, 0.2, 0.2)
leftHand:set_material(tan)
leftHandNode:add_child(leftHand)

-- right arm
rightArmNode = gr.node('rightArmNode')
body:add_child(rightArmNode)
rightArmNode:scale(1.0/0.7, 1.0/0.8, 1.0/0.5)
rightArmNode:translate(0.8, 0.35, 0.0)

rightArm = gr.sphere('sphere')
rightArm:scale(0.2, 0.4, 0.2)
rightArm:rotate('z', 30.0)
rightArm:translate(0.1, -0.2, 0.0)
rightArm:set_material(yellow)
rightArmNode:add_child(rightArm)

-- right forearm
rightForearmNode = gr.node('rightForearmNode')
rightForearmNode:scale(1.0/0.2, 1.0/0.4, 1.0/0.2)
rightArm:add_child(rightForearmNode)
rightForearmNode:translate(0.0, -1.1, 0.0)

rightForearm = gr.sphere('sphere')
rightForearm:scale(0.17, 0.35, 0.17)
rightForearm:translate(0.0, -0.2, 0.0)
rightForearm:set_material(yellow)
rightForearmNode:add_child(rightForearm)

-- right hand
rightHandNode = gr.node('rightHandNode')
rightHandNode:scale(1.0/0.17, 1.0/0.35, 1.0/0.17)
rightForearm:add_child(rightHandNode)
rightHandNode:translate(0.0, -1.2, 0.0)

rightHand = gr.sphere('sphere')
rightHand:scale(0.2, 0.2, 0.2)
rightHand:set_material(tan)
rightHandNode:add_child(rightHand)

-- hips
hipsNode = gr.node('hipsNode')
body:add_child(hipsNode)
hipsNode:scale(1.0/0.7, 1.0/0.8, 1.0/0.5)
hipsNode:translate(0.0, -0.65, 0.0)

hips = gr.sphere('sphere')
hips:scale(0.65, 0.5, 0.4)
hips:set_material(blue)
hipsNode:add_child(hips)

-- left thigh
leftThighNode = gr.node('leftThighNode')
hips:add_child(leftThighNode)
leftThighNode:scale(1.0/0.65 / 0.9, 1.0/0.5 / 0.6, 1.0/0.4 / 0.9)
leftThighNode:translate(-0.42, -1.15, 0.0)

leftThigh = gr.sphere('sphere')
leftThigh:scale(0.25, 0.4, 0.25)
leftThigh:set_material(blue)
leftThighNode:add_child(leftThigh)

-- left shin
leftShinNode = gr.node('leftShinNode')
leftThigh:add_child(leftShinNode)
leftShinNode:scale(1.0/0.25, 1.0/0.4, 1.0/0.25)
leftShinNode:translate(0.0, -0.85, 0.0)

leftShin = gr.sphere('sphere')
leftShin:scale(0.17, 0.3, 0.17)
leftShin:translate(0.0, -0.2, 0.0)
leftShin:set_material(blue)
leftShinNode:add_child(leftShin)

-- left foot
leftFootNode = gr.node('leftFootNode')
leftShin:add_child(leftFootNode)
leftFootNode:scale(1.0/0.17, 1.0/0.3, 1.0/0.17)
leftFootNode:translate(0.0, -1.2, 0.0)

leftFoot = gr.sphere('sphere')
leftFoot:scale(0.18, 0.14, 0.25)
leftFoot:set_material(red)
leftFootNode:add_child(leftFoot)

-- right thigh
rightThighNode = gr.node('rightThighNode')
hips:add_child(rightThighNode)
rightThighNode:scale(1.0/0.65 / 0.9, 1.0/0.5 / 0.6, 1.0/0.4 / 0.9)
rightThighNode:translate(0.42, -1.15, 0.0)

rightThigh = gr.sphere('sphere')
rightThigh:scale(0.25, 0.4, 0.25)
rightThigh:set_material(blue)
rightThighNode:add_child(rightThigh)

-- right shin
rightShinNode = gr.node('rightShinNode')
rightThigh:add_child(rightShinNode)
rightShinNode:scale(1.0/0.25, 1.0/0.4, 1.0/0.25)
rightShinNode:translate(0.0, -0.85, 0.0)

rightShin = gr.sphere('sphere')
rightShin:scale(0.17, 0.3, 0.17)
rightShin:translate(0.0, -0.2, 0.0)
rightShin:set_material(blue)
rightShinNode:add_child(rightShin)

-- right foot
rightFootNode = gr.node('rightFootNode')
rightShin:add_child(rightFootNode)
rightFootNode:scale(1.0/0.17, 1.0/0.3, 1.0/0.17)
rightFootNode:translate(0.0, -1.2, 0.0)

rightFoot = gr.sphere('sphere')
rightFoot:scale(0.18, 0.14, 0.23)
rightFoot:set_material(red)
rightFootNode:add_child(rightFoot)

-- trees

reflect = gr.sphere('sphere')
reflect:set_material(glass)
reflect:scale(1, 1, 1)
reflect:translate(-4.0, 6.0, -5.0)
scene_root:add_child(reflect)

cone1 = gr.nh_cone('cone1', {-9, 4, -4}, 5)
scene_root:add_child(cone1)
cone1:set_material(green2)

cone2 = gr.nh_cone('cone2', {-5, 3, -8}, 9)
scene_root:add_child(cone2)
cone2:set_material(green2)

cone3 = gr.nh_cone('cone3', {1, 3, -4}, 7)
scene_root:add_child(cone3)
cone3:set_material(green)

cone4 = gr.nh_cone('cone4', {-8, 3, 3}, 4)
scene_root:add_child(cone4)
cone4:set_material(green)

cone5 = gr.nh_cone('cone5', {3, 3, 3}, 4)
scene_root:add_child(cone5)
cone5:set_material(green)

light = gr.light({0, 4.0, -10.0 / 2.0 - 2.0}, {0.5, 0.5, 0.5}, {5, 2, 0})
light_2 = gr.light({-1.0, 2.0, -5}, {255 / 255, 251 / 255, 235 / 255}, {1, 0, 0})

wintersecte_light = gr.light({-100.0, 150.0, 400.0}, {0.9, 0.9, 0.9}, {1, 0, 0})
magenta_light = gr.light({300.0, 100.0, 400.0}, {0.7, 0.7, 0.7}, {1, 0, 0})

gr.render(scene_root, 'finalScene.png', 500, 500,
	  {0.0, 10.0, 15.0}, {0, 0, -10.0 / 2.0}, {0, 1, 0}, 50,
	  {0.3, 0.3, 0.3}, {wintersecte_light, magenta_light})
