/*---------------------------------------------------------------------- */
/*                                                                       */
/* Lofi aerodata                                                         */
/* taken from Richard S. Russell's F-16 model                            */
/*                                                                       */
/*---------------------------------------------------------------------- */
int fix(double);
int sign(double);

/* Damping Aero-Coeffs */
void damping(double alpha, double *coeff){

    double s, da;

    double A[9][12] = {
{-.267, .110,  .308,  1.34,  2.08,  2.91,  2.76,  2.05,   1.5,  1.49,  1.83,  1.21},
{ .882,  .852,  .876,  .958,  .962,  .974,  .819,  .483,  .590,  1.21, -.493, -1.04},
{-.108, -.108, -.188,  .110,  .258,  .226,  .344,  .362,  .611,  .529,  .298, -2.27},
{ -8.8, -25.8, -28.9, -31.4, -31.2, -30.7, -27.7, -28.2,   -29, -29.8, -38.3, -35.3},
{-.126, -.026,  .063,  .113,  .208,  .230,  .319,  .437,  .680,    .1,  .447, -.330},
{ -.36, -.359, -.443,  -.42, -.383, -.375, -.329, -.294,  -.23,  -.21,  -.12,   -.1},
{-7.21,  -.54, -5.23, -5.26, -6.11, -6.64, -5.69,    -6,  -6.2,  -6.4,  -6.6,    -6},
{ -.38, -.363, -.378, -.386,  -.37, -.453,  -.55, -.582, -.595, -.637, -1.02,  -.84},
{ .061,  .052,  .052, -.012, -.013, -.024,   .05,   .15,   .13,  .158,   .24,   .15}};

    int k, L;

    /*  Begin Interp */
    s = .2*(alpha);
    k = fix(s);
    if (k <= -2) {               /*bounds of table for extrapolation*/
        k = -1;
    }
    else if (k >= 9){
        k = 8;
    }
    da = s - k;         /* amount from closest lower grid point*/

    /*L = k + fix(1.1*(da/fabs(da)));*/   
    L = k + fix(1.1*sign(da));
   
    k = k + 3;
    L = L + 3;

    coeff[0] = A[0][k-1] + fabs(da)*(A[0][L-1] - A[0][k-1]);
    coeff[1] = A[1][k-1] + fabs(da)*(A[1][L-1] - A[1][k-1]);
    coeff[2] = A[2][k-1] + fabs(da)*(A[2][L-1] - A[2][k-1]);
    coeff[3] = A[3][k-1] + fabs(da)*(A[3][L-1] - A[3][k-1]);
    coeff[4] = A[4][k-1] + fabs(da)*(A[4][L-1] - A[4][k-1]);
    coeff[5] = A[5][k-1] + fabs(da)*(A[5][L-1] - A[5][k-1]);
    coeff[6] = A[6][k-1] + fabs(da)*(A[6][L-1] - A[6][k-1]);
    coeff[7] = A[7][k-1] + fabs(da)*(A[7][L-1] - A[7][k-1]);	
    coeff[8] = A[8][k-1] + fabs(da)*(A[8][L-1] - A[8][k-1]);
}

/* Function for relations to control inputs */
void dmomdcon(double alpha, double beta, double *coeff){

    int fix(double);

    double s, da, db, dlda, dldr, dnda, dndr;
    double t, u, v, w;

    double ALA[7][12] = {
{-.041, -.052, -.053, -.056, -.050, -.056, -.082, -.059, -.042, -.038, -.027, -.017},
{-.041, -.053, -.053, -.053, -.050, -.051, -.066, -.043, -.038, -.027, -.023, -.016},
{-.042, -.053, -.052, -.051, -.049, -.049, -.043, -.035, -.026, -.016, -.018, -.014},
{-.040, -.052, -.051, -.052, -.048, -.048, -.042, -.037, -.031, -.026, -.017, -.012},
{-.043, -.049, -.048, -.049, -.043, -.042, -.042, -.036, -.025, -.021, -.016, -.011},
{-.044, -.048, -.048, -.047, -.042, -.041, -.020, -.028, -.013, -.014, -.011, -.010},
{-.043, -.049, -.047, -.045, -.042, -.037, -.003, -.013, -.010, -.003, -.007, -.008}
};

    double ALR[7][12] = {
{.005, .017, .014, .010, -.005, .009, .019, .005,   0.0, -.005, -.011, .008},
{.007, .016, .014, .014,  .013, .009, .012, .005,   0.0,  .004,  .009, .007},
{.013, .013, .011, .012,  .011, .009, .008, .005, -.002,  .005,  .003, .005},
{.018, .015, .015, .014,  .014, .014, .014, .015,  .013,  .011,  .006, .001},
{.015, .014, .013, .013,  .012, .011, .011, .010,  .008,  .008,  .007, .003},
{.021, .011, .010, .011,  .010, .009, .008, .010,  .006,  .005,   0.0, .001},
{.023, .010, .011, .011,  .011, .010, .008, .010,  .006,  .014,  .020,  0.0}
};

    double ANA[7][12] = {
{ .001, -.027, -.017, -.013, -.012, -.016,  .001,  .017,  .011, .017,  .008, .016},
{ .002, -.014, -.016, -.016, -.014, -.019, -.021,  .002,  .012, .016,  .015, .011},
{-.006, -.008, -.006, -.006, -.005, -.008, -.005,  .007,  .004, .007,  .006, .006},
{-.011, -.011, -.010, -.009, -.008, -.006,   0.0,  .004,  .007, .010,  .004, .010},
{-.015, -.015, -.014, -.012, -.011, -.008, -.002,  .002,  .006, .012,  .011, .011},
{-.024, -.010, -.004, -.002, -.001,  .003,  .014,  .006, -.001, .004,  .004, .006},
{-.022,  .002, -.003, -.005, -.003, -.001, -.009, -.009, -.001, .003, -.002, .001}
};

    double ANR[7][12] = {
{-.018, -.052, -.052, -.052, -.054, -.049, -.059, -.051, -.030, -.037, -.026, -.013},
{-.028, -.051, -.043, -.046, -.045, -.049, -.057, -.052, -.030, -.033, -.030, -.008},
{-.037, -.041, -.038, -.040, -.040, -.038, -.037, -.030, -.027, -.024, -.019, -.013},
{-.048, -.045, -.045, -.045, -.044, -.045, -.047, -.048, -.049, -.045, -.033, -.016},
{-.043, -.044, -.041, -.041, -.040, -.038, -.034, -.035, -.035, -.029, -.022, -.009},
{-.052, -.034, -.036, -.036, -.035, -.028, -.024, -.023, -.020, -.016, -.010, -.014},
{-.062, -.034, -.027, -.028, -.027, -.027, -.023, -.023, -.019, -.009, -.025, -.010}
};

    int k, L, m, n;

    /*  Begin Interp */
    s = .2*(alpha);
    k = fix(s);
    if (k <= -2) {               /*bounds of table for extrapolation*/
        k = -1;
    }
    else if (k >= 9){
        k = 8;
    }
    da = s - k;         /* amount from closest lower grid point*/

    /* L = k + fix(1.1*(da/fabs(da))); */
    L = k + fix(1.1*sign(da));

	/* There seems to be some confusion about the range of beta in these tables. 
	According to Lewis and Stevens beta runs from -30 to 30, but according to russell
	it should be 0 to 30. After some testing, it appears that Lewis and Stevens are right,
	using the tables for  beta -30 to 30 gives a response more similar to the model in NASA
	report 1538. */

    s = 0.1*beta;
    m = fix(s);
   
    if (m <= -3){
        m = -2;
    }
    else if (m >= 3){
        m = 2;
    }

    db = s - m;

    n = m + fix(1.1*sign(db));
    
    /*boundary condition*/
    if (n < -3){
        n = -3;
    }
   else if (n > 3){
        n = 3;
   }
    
    k = k + 3;
    L = L + 3;
    m = m + 4;   
    n = n + 4;

    /* dLda */
   
    t = ALA[m-1][k-1];
    u = ALA[n-1][k-1];
    v = t + fabs(da)*(ALA[m-1][L-1] - t);
    w = u + fabs(da)*(ALA[n-1][L-1] - u);
    dlda = v + (w-v)*db;

    /* dLdr */

    t = ALR[m-1][k-1];
    u = ALR[n-1][k-1];
    v = t + fabs(da)*(ALR[m-1][L-1] - t);
    w = u + fabs(da)*(ALR[n-1][L-1] - u);
    dldr = v + (w-v)*db;

    /* dNda */

    t = ANA[m-1][k-1];
    u = ANA[n-1][k-1];
    v = t + fabs(da)*(ANA[m-1][L-1] - t);
    w = u + fabs(da)*(ANA[n-1][L-1] - u);
    dnda = v + (w-v)*db;

    /* dNdr */

    t = ANR[m-1][k-1];
    u = ANR[n-1][k-1];
    v = t + fabs(da)*(ANR[m-1][L-1] - t);
    w = u + fabs(da)*(ANR[n-1][L-1] - u);
    dndr = v + (w-v)*db;

    coeff[0] = dlda;
    coeff[1] = dldr;
    coeff[2] = dnda;
    coeff[3] = dndr;
}

void clcn(double alpha, double beta, double *coeff){
    int fix(double);
    int sign(double);    


    double s, da, db, cl, cn; 
    double t, u, v, w, dum;
    double AL[7][12] = {{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},
{-.001,-.004,-.008,-.012,-.016,-.019,-.020,-.020,-.015,-.008,-.013,-.015},
{-.003,-.009,-.017,-.024,-.030,-.034,-.040,-.037,-.016,-.002,-.010,-.019},
{-.001,-.010,-.020,-.030,-.039,-.044,-.050,-.049,-.023,-.006,-.014,-.027},
{    0,-.010,-.022,-.034,-.047,-.046,-.059,-.061,-.033,-.036,-.035,-.035},
{ .007,-.010,-.023,-.034,-.049,-.046,-.068,-.071,-.060,-.058,-.062,-.059},
{ .009,-.011,-.023,-.037,-.050,-.047,-.074,-.079,-.091,-.076,-.077,-.076}};

    double AN[7][12] = {{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},
{ .018, .019, .018, .019, .019, .018, .013, .007, .004, -.014, -.017, -.033},
{ .038, .042, .042, .042, .043, .039, .030, .017, .004, -.035, -.047, -.057},
{ .056, .057, .059, .058, .058, .053, .032, .012, .002, -.046, -.071, -.073},
{ .064, .077, .076, .074, .073, .057, .029, .007, .012, -.034, -.065, -.041},
{ .074, .086, .093, .089, .080, .062, .049, .022, .028, -.012, -.002, -.013},
{ .079, .090, .106, .106, .096, .080, .068, .030, .064,  .015,  .011, -.001}};

    int k, L, m, n;
    /*  Begin Interp */
    s = .2*(alpha);
    k = fix(s);
    if (k <= -2) {               /*bounds of table for extrapolation*/
        k = -1;
    }
    else if (k >= 9){
        k = 8;
    }
    da = s - k;         /* amount from closest lower grid point*/

    /* L = k + fix(1.1*(da/fabs(da))); */
    L = k + fix(1.1*sign(da));

    s = .2*fabs(beta);
    m = fix(s);
    if (m == 0) {               /*bounds of table for extrapolation*/
        m = 1;
    }
    else if (m >= 6){
        m = 5;
    }
    db = s - m;
    /* n = m+fix(1.1*db/fabs(db)); */
    n = m+fix(1.1*sign(db));
    
   

    k = k + 3;
    L = L + 3;
    m = m + 1;
    n = n + 1;

    /* CL */

    t = AL[m-1][k-1];
    u = AL[n-1][k-1];
    v = t + fabs(da)*(AL[m-1][L-1] - t);
    w = u + fabs(da)*(AL[n-1][L-1] - u);
    dum = v + (w-v)*fabs(db);
    cl = dum*sign(beta);

   /* CN */

    t = AN[m-1][k-1];
    u = AN[n-1][k-1];
    v = t + fabs(da)*(AN[m-1][L-1] - t);
    w = u + fabs(da)*(AN[n-1][L-1] - u);
    dum = v + (w-v)*fabs(db);
    cn = dum*sign(beta); 

    coeff[0] = cl;
    coeff[1] = cn;
}

/*Cx and Cm aero-coeffs */
void cxcm(double alpha, double dele, double *coeff){

    int fix(double);
    double s, da, de, cx, cm, cx0, cm0; 
    double t, u, v, w;

    double AX[5][12] = {
{-.099, -.081, -.081, -.063, -.025, .044, .097, .113, .145, .167, .174, .166},
{-.048, -.038, -.040, -.021,  .016, .083, .127, .137, .162, .177, .179, .167},
{-.022, -.020, -.021, -.004,  .032, .094, .128, .130, .154, .161, .155, .138},
{-.040, -.038, -.039, -.025,  .006, .062, .087, .085, .100, .110, .104, .091},
{-.083, -.073, -.076, -.072, -.046, .012, .024, .025, .043, .053, .047, .040}};

    double AM[5][12] = {
{ .205,  .168,  .186,  .196,  .213,  .251,  .245,  .238,  .252,  .231,  .198,  .192},
{ .081,  .077,  .107,  .110,  .110,  .141,  .127,  .119,  .133,  .108,  .081,  .093},
{-.046, -.020, -.009, -.005, -.006,  .010,  .006, -.001,  .014,   0.0, -.013,  .032},
{-.174, -.145, -.121, -.127, -.129, -.102, -.097, -.113, -.087, -.084, -.069, -.006},
{-.259, -.202, -.184, -.193, -.199, -.150, -.160, -.167, -.104, -.076, -.041, -.005}};

    double AX0[5][12] = {
{-.0906, -.0822, -.0804, -.0671, -.0354, .0204, .0538, .0558, .0764, .0934, .0915, .0820},
{-.0440, -.0386, -.0397, -.0230, .0110, .0717, .1063, .1095, .1290, .1417, .1394, .1267},
{-.0220, -.0200, -.0210, -.0040, .0320, .0940, .1280, .1300, .1540, .1610, .1550, .1380},
{-.0440, -.0374, -.0393, -.0230, .0110, .0733, .1077, .1125, .1330, .1453, .1436, .1313},
{-.0914, -.0718, -.0766, -.0679, -.0356, .0356, .0672, .0822, .1116, .1266, .1295, .1240}};    

    double AM0[5][12] = {
{-.0707, -.0771, -.0672, -.0666, -.0488, -.0179, .0024, -.0154, .0075, .0171, .0307, .0875},
{-.0513, -.0406, -.0145, -.0160, -0.0157, .0119, .0106, -.0026, .0156, .0053, .0007, .0428},
{-.046, -.020, -.009, -.005, -.006,  .010,  .006, -.001,  .014,   0.0, -.013,  .032},
{-.0417, -.0274, .0005, -.0010, -.0033, .0271, .0194, .0086, .0304, .0187, .0113, .0442},
{.0167, .0431, .0692, .0696, .0628, .1189, .0826, .0864, .1405, .1379, .1263, .0995}};
        
        
    int k, L, m, n;

    /*  Begin Interp */
    s = .2*(alpha);
    k = fix(s);
    if (k <= -2) {               /*bounds of table for extrapolation*/
        k = -1;
    }
    else if (k >= 9){
        k = 8;
    }
    da = s - k;         /* amount from closest lower grid point*/

    /* L = k + fix(1.1*(da/fabs(da))); */
    L = k + fix(1.1*sign(da)); 

    s = dele/12.0;
    m = fix(s);
    if (m <= -2){
        m = -1;
    }
    else if (m >= 2){
        m = 1;
    }
    de = s - m;
    /* n = m + fix(1.1*de/fabs(de)); */
    n = m + fix(1.1*sign(de));

    k = k + 3;
    L = L + 3;
    m = m + 3;
    n = n + 3;

    /* CX */

    t = AX[m-1][k-1];
    u = AX[n-1][k-1];
    v = t + fabs(da)*(AX[m-1][L-1] - t);
    w = u + fabs(da)*(AX[n-1][L-1] - u);
    cx = v + (w-v)*fabs(de);
    
    /* CX0 */

    t = AX0[m-1][k-1];
    u = AX0[n-1][k-1];
    v = t + fabs(da)*(AX0[m-1][L-1] - t);
    w = u + fabs(da)*(AX0[n-1][L-1] - u);
    cx0 = v + (w-v)*fabs(de);

    /* CM */

    t = AM[m-1][k-1];
    u = AM[n-1][k-1];
    v = t + fabs(da)*(AM[m-1][L-1] - t);
    w = u + fabs(da)*(AM[n-1][L-1] - u);
    cm = v + (w-v)*fabs(de);
    
    /* CM0 */

    t = AM0[m-1][k-1];
    u = AM0[n-1][k-1];
    v = t + fabs(da)*(AM0[m-1][L-1] - t);
    w = u + fabs(da)*(AM0[n-1][L-1] - u);
    cm0 = v + (w-v)*fabs(de);

    coeff[0] = cx;
    coeff[1] = cm;
    coeff[2] = cx0;
    coeff[3] = cm0;
    
}

/* Cz aero-coeff */
void cz(double alpha,double beta, double dele, double *coeff){

    int fix(double);
    double s, da, cz, cz0, czde; 
    double A[] = {.770, .241, -.100, -.416, -.731, -1.053, -1.366, 
                    -1.646, -1.917, -2.120, -2.248, -2.229};
    int k, L;
 
    s = .2*(alpha);
    k = fix(s);

    if (k <= -2) {               /*bounds of table for extrapolation*/
        k = -1;
    }
    else if (k >= 9){
        k = 8;
    }

    da = s - k;         /* amount from closest lower grid point*/

    /* L = k + fix(1.1*(da/fabs(da))); */ 
    L = k + fix(1.1*sign(da));

    k = k + 3;
    L = L + 3;

    s = A[k-1] + fabs(da)*(A[L-1]-A[k-1]);
    cz = s*(1-pow((beta/57.3),2))-.19*(dele)/25;
    cz0 = s*(1-pow((beta/57.3),2));
    czde = -.19/(25*3.14159265/180);
    
    coeff[0] = cz;
    coeff[1] = cz0;
    coeff[2] = czde;
}

/* Cxde and Cmde aero-coeff */
void cxcmde(double alpha, double *coeff){

    int fix(double);
    double s, da, cxde, cmde; 
    double AX[] = {.0193, -.0027, .0014, -.0093, -.0238, -.0542, -.0990,
            -.1311, -.1573, -.1687, -.1891, -.1925};
    double AM[] = {-.6318, -.5617, -.5803, -.6017, -.6000, -.6162, -.5559, 
            -.5807, -.5603, -.4903, -.3833, -.2395};
            
    int k, L;
 
    s = .2*(alpha);
    k = fix(s);

    if (k <= -2) {               /*bounds of table for extrapolation*/
        k = -1;
    }
    else if (k >= 9){
        k = 8;
    }

    da = s - k;         /* amount from closest lower grid point*/

    /* L = k + fix(1.1*(da/fabs(da))); */ 
    L = k + fix(1.1*sign(da));

    k = k + 3;
    L = L + 3;

    cxde = AX[k-1] + fabs(da)*(AX[L-1]-AX[k-1]);
    cmde = AM[k-1] + fabs(da)*(AM[L-1]-AM[k-1]);
    
    coeff[0] = cxde;
    coeff[1] = cmde;

}

int fix(double in){
    int out;

    if (in >= 0.0){
       out = (int)floor(in);
    }
    else if (in < 0.0){
       out = (int)ceil(in);
    }

    return out;
}

int sign(double in){
    int out;

    if (in > 0.0){
       out = 1;
    }
    else if (in < 0.0){
       out = -1;
    }
    else if (in == 0.0){
       out = 0;
    }
    return out;
}
