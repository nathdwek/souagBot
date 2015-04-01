//Constantes du PIC
const long PROC_FCY = 40000000;

//Constantes de la régulation
const int REGUL_FCY = 100;
const float CM_PER_TICK = 0.08;
const float ACCELERATION = 50;//cm par seconde au carré
const float ANGULAR_ACCELERATION = 2;//radians par seconde au carré
const float MAIN_KP = 0.00006;//kp max pour pas sortir de 0.1-0.2 de rapport cyclique
const float PERTURB_KP = 0.2;//et pas d'oscillation autour de la ligne droite
const float MAX_SPEED = 40;// cm par seconde
const float MAX_ANGULAR_SPEED = 3.55;//radian par seconde
