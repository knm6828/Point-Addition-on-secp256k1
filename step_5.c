// point_y = (-(s_y + m * (point_x - s_x))) % p;

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
	// The diff is -ve. Think what to do here!!! Maybe subtract with P Or take 2's complement and sub with P
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






for (i = 0; i < 24; i++)
{
	m3[i] = 0;
   carry_helper3[i] = 0;
}


for (i = 7; i >= 0; i--)
      {
          if (i % 2 == 1)
          {
             helper_2 = k1[i/2] & 0x00000000ffffffff;
          }
          else
          {
             helper_2 = (k1[i/2] & 0xffffffff00000000)>>32;
          }

         for(j = 15; j >= 0; j--)
         {
            helper_1 = m[j];

            if(carry_helper3[i+j+1] != 0)
            {
               if (m3[i+j+1] > MAX_VALUE_INT - carry_helper3[i+j+1])
               {
                  carry_helper3[i+j]++;
               }
               m3[i+j+1] += carry_helper3[i+j+1];
               carry_helper3[i+j+1] = 0;
            }


            temp = helper_1;
             temp *= helper_2;
             temp_1 = temp & 0x00000000ffffffff;
             if (m3[i+j+1] > MAX_VALUE_INT - temp_1)
             {
               carry_helper3[i+j]++;
             }
             m3[i+j+1] += temp_1;
             

             temp_1 = (temp & 0xffffffff00000000)>>32;
             if (m3[i+j] > MAX_VALUE_INT - temp_1)
             {
               carry_helper3[i+j-1]++;
             }
             m3[i+j] += temp_1;
          
         }
      }

      m3[0] += carry_helper3[0];


























for (i = 0; i < 24; i++)
{
   carry_helper3[i] = 0;
}


helper_1 = s_y[3] & 0x00000000ffffffff;
	if (m3[23] > MAX_VALUE_INT - helper_1)
	{
		carry_helper3[23] = 1;
	}
	m3[23] += helper_1;
	for (i = 22; i >= 0; i--)
	{
		if (i < 16)
		{
			helper_1 = 0;
			// Maybe i can add carry_helper and break?? What is it's all f's? U need to iterate completely to check carry_helper3[0]
		}
		else if(i%2 == 0)
		{
			helper_1 = (s_y[(i-16)/2] & 0xffffffff00000000)>>32;
		}
		else
		{
			helper_1 = s_y[(i-16)/2] & 0x00000000ffffffff;
		}

		if (m3[i] < MAX_VALUE_INT - helper_1)
	 	{
		    m3[i] += helper_1 + carry_helper3[i+1];
	 	}
	 	else if (m3[i] > MAX_VALUE_INT - helper_1)
	 	{
		    carry_helper3[i] = 1; 
		    m3[i] += helper_1 + carry_helper3[i+1];  // This temp_overflow is not gonna cause another overflow (f+f=1e which is 1 less than 1f)
	 	}
	 	else
	 	{
		    if(carry_helper3[i+1] == 1)
		    {
		       carry_helper3[i] = 1;
		       m3[i] = 0;
		    }
		    else
		    {
		       m3[i] = 0xffffffff;
		    }
	 	}
	}

// carry_helper3[0] contains the overflow bit. You cant neglect this
// 32*24 + 1 is the no of bits p should have with msb being 1



for (i = 0; i < 7; i++)
{
	m2[i] = 0;
}
m2[7] = carry_helper3[0];
for (i = 8; i < 32; i++)
{
	m2[i] = m3[i-8];
}


 			for (i = 0; i < 32; i++)
         {
            mod_helper[i] = 0;
         }


			for (i = 0; i < 769; i++)
         {
		            if(i%32 == 0)
		            {
		               if (i/32 != 0)
		               {
		                  mod_helper[(i/32) - 1] = 0;
		                
		               }
		               for (j = 0; j < 8; j++)
		               {
		                  mod_helper[i/32 + j] = p_mod[32*9 - 1 - 8 + j];
		               }
		              
		            }
		            else
		            {
		               for (j = 0; j < 9; j++)
		               {
		                  mod_helper[i/32 + j] = p_mod[(32-(i%32))*9 - 1 - 8 + j];
		               }
		               
		            }
		           
		            // Now check if m2 is greater than mod_helper. If yes, subtract mod_helper from m2

		            greater = 0;
		            for (j = 0; j < 32; j++)
		            {
		               if (m2[j] > mod_helper[j])
		               {
		                  greater = 1;
		                  break;
		               }
		                if (m2[j] < mod_helper[j])
		               {
		                  break;
		               }
		            }
		            // It wont be equal!



		            




		            if (greater == 1)
		            {
		              
		            
				               for (j = 0; j < 32; j++)
				               {
				                  mod_helper_1[j] = ~(mod_helper[j]);
				               }

				               for (j = 31; j >= 0; j--)
				               {  
				                  if (mod_helper_1[j] == 0xffffffff)
				                  {
				                     mod_helper_1[j] = 0;
				                     continue;
				                  }
				                  mod_helper_1[j] += 1;
				                  break;
				               }

				               for (j = 0; j < 32; j++)
				               {
				                  carry_helper2[j] = 0;
				               }

				               // add m2 and mod_helper_1

				               if (m2[31] > MAX_VALUE_INT - mod_helper_1[31])
				               {
				                  carry_helper2[31] = 1;
				               }
				               m2[31] += mod_helper_1[31];
				               for (j = 30; j >= 0; j--)
				               {
				                  if (m2[j] < MAX_VALUE_INT - mod_helper_1[j])
				                  {
				                      m2[j] += mod_helper_1[j] + carry_helper2[j+1];
				                  }
				                  else if (m2[j] > MAX_VALUE_INT - mod_helper_1[j])
				                  {
				                      carry_helper2[j] = 1; 
				                      m2[j] += mod_helper_1[j] + carry_helper2[j+1]; 
				                  }
				                  else
				                  {
				                      if(carry_helper2[j+1] == 1)
				                      {
				                         carry_helper2[j] = 1;
				                         m2[j] = 0;
				                      }
				                      else
				                      {
				                         m2[j] = 0xffffffff;
				                      }
				                  }
				               }

						}


				}




for (i = 30; i >= 24; i -= 2)
{
	temp = m2[i];
	temp = temp<<32;
	point_y[(i-24)/2] = ~(temp + m2[i+1]);
}
for (i = 3; i >=0; i--)
{
	if (point_y[i] == 0xffffffffffffffff)
	{
		point_y[i] = 0;
		continue;
	}
	point_y[i]++;
	break;
}
temp_overflow[0] = 0; temp_overflow[1] = 0; temp_overflow[2] = 0; temp_overflow[3] = 0;
if (point_y[3] > MAX_VALUE_LONG - p[3])
{
	temp_overflow[3] = 1;
}
point_y[3] += p[3];
for (i = 2; i >= 0; i--)
{
	if (point_y[i] < MAX_VALUE_LONG - p[i])
 	{
	    point_y[i] += p[i] + temp_overflow[i+1];
 	}
 	else if (point_y[i] > MAX_VALUE_LONG - p[i])
 	{
	    temp_overflow[i] = 1; 
	    point_y[i] += p[i] + temp_overflow[i+1];  // This temp_overflow is not gonna cause another overflow (f+f=1e which is 1 less than 1f)
 	}
 	else
 	{
	    if(temp_overflow[i+1] == 1)
	    {
	       temp_overflow[i] = 1;
	       point_y[i] = 0;
	    }
	    else
	    {
	       point_y[i] = 0xffffffffffffffff;
	    }
 	}
}








}