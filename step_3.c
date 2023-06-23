//m = (point_y - s_y) * m1;
//k1 = (point_y - s_y);
//m = k1 * m1;

// point_y unsigned long[4]
// s_2_y unsigned long[4]
// m1 unsigned long[4]
// m unsigned int[16]
// p unsigned long[4]

temp_overflow[0] = 0; temp_overflow[1] = 0; temp_overflow[2] = 0; temp_overflow[3] = 0;
if (point_y[3] > MAX_VALUE_LONG - s_2_y[3])
{
	temp_overflow[3] = 1;
}
k1[3] = point_y[3] + s_2_y[3];
for (i = 2; i >= 0; i--)
{
	if (point_y[i] < MAX_VALUE_LONG - s_2_y[i])
 	{
	    k1[i] = point_y[i] + s_2_y[i] + temp_overflow[i+1];
 	}
 	else if (point_y[i] > MAX_VALUE_LONG - s_2_y[i])
 	{
	    temp_overflow[i] = 1; 
	    k1[i] = point_y[i] + s_2_y[i] + temp_overflow[i+1];  // This temp_overflow is not gonna cause another overflow (f+f=1e which is 1 less than 1f)
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
	temp_overflow[1] = 0; temp_overflow[2] = 0; temp_overflow[3] = 0;


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

//k1 256 bits - 4 long elements
//m1 256 bits - 4 long elements







//maybe i can make carry_helper boolean

for (i = 0; i < 16; i++)
      {
         m[i] = 0;
         carry_helper[i] = 0;
      }

      for (i = 7; i >= 0; i--)
      {
          if (i % 2 == 1)
          {
             helper_2 = m1[i/2] & 0x00000000ffffffff;
          }
          else
          {
             helper_2 = (m1[i/2] & 0xffffffff00000000)>>32;
          }

         for(j = 7; j >= 0; j--)
         {
            if (j % 2 == 1)
             {
                helper_1 = k1[j/2] & 0x00000000ffffffff;
             }
             else
             {
                helper_1 = (k1[j/2] & 0xffffffff00000000)>>32;
             }
            

            if(carry_helper[i+j+1] != 0)
            {
               if (m[i+j+1] > MAX_VALUE_INT - carry_helper[i+j+1])
               {
                  carry_helper[i+j]++;
               }
               m[i+j+1] += carry_helper[i+j+1];
               carry_helper[i+j+1] = 0;
            }


            temp = helper_1;
             temp *= helper_2;
             temp_1 = temp & 0x00000000ffffffff;
             if (m[i+j+1] > MAX_VALUE_INT - temp_1)
             {
               carry_helper[i+j]++;
             }
             m[i+j+1] += temp_1;
             

             temp_1 = (temp & 0xffffffff00000000)>>32;
             if (m[i+j] > MAX_VALUE_INT - temp_1)
             {
               carry_helper[i+j-1]++;// this wont go to -ve values because 256 bits * 256 bits <= 512 bits
             }
             m[i+j] += temp_1;
          
         }
      }

      m[0] += carry_helper[0];

