// k1 = point_x - s_x
// point_x unsigned long[4]
// s_2_x unsigned long[4]
// k1 unsigned long[4]
// p unsigned long[4]
for(looper = 0; looper < 0xffff; looper++){
temp_overflow[0] = 0; temp_overflow[1] = 0; temp_overflow[2] = 0; temp_overflow[3] = 0;
if (point_x[3] > MAX_VALUE_LONG - s_2_x[3])
{
	temp_overflow[3] = 1;
}
k1[3] = point_x[3] + s_2_x[3];
for (i = 2; i >= 0; i--)
{
	if (point_x[i] < MAX_VALUE_LONG - s_2_x[i])
 	{
	    k1[i] = point_x[i] + s_2_x[i] + temp_overflow[i+1];
 	}
 	else if (point_x[i] > MAX_VALUE_LONG - s_2_x[i])
 	{
	    temp_overflow[i] = 1; 
	    k1[i] = point_x[i] + s_2_x[i] + temp_overflow[i+1];  // This temp_overflow is not gonna cause another overflow (f+f=1e which is 1 less than 1f)
 	}
 	else
 	{
	    if(temp_overflow[i+1] == 1)
	    {
	       temp_overflow[i] = 1;
	       k1[i] = 0;
	    }
	    else
	    {
	       k1[i] = 0xffffffffffffffff;
	    }
 	}
}
if (temp_overflow[0] == 0)
{

	temp_overflow[0] = 0; temp_overflow[1] = 0; temp_overflow[2] = 0; temp_overflow[3] = 0;


	if (p[3] > MAX_VALUE_LONG - k1[3])
	{
		temp_overflow[3] = 1;
	}
	k1[3] += p[3];
	for (i = 2; i >= 0; i--)
	{
		if (p[i] < MAX_VALUE_LONG - k1[i])
	 	{
		    k1[i] += p[i] + temp_overflow[i+1];
	 	}
	 	else if (p[i] > MAX_VALUE_LONG - k1[i])
	 	{
		    temp_overflow[i] = 1; 
		    k1[i] += p[i] + temp_overflow[i+1];  // This temp_overflow is not gonna cause another overflow (f+f=1e which is 1 less than 1f)
	 	}
	 	else
	 	{
		    if(temp_overflow[i+1] == 1)
		    {
		       temp_overflow[i] = 1;
		       k1[i] = 0;
		    }
		    else
		    {
		       k1[i] = 0xffffffffffffffff;
		    }
	 	}
	}
}

