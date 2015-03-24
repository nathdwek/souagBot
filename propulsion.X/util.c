int sgn(float number){
    float epsilon = 5 ;
    if (number > epsilon)
        return 1;
    else if (number < -epsilon)
        return -1;
    else
        return 0;
}
