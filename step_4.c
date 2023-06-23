// point_x = (m * m - s_x - point_x) % p;
// m2 1024 bits - int (1024/32 = 32 elements)




for (i = 0; i < 32; i++)
      {
         m2[i] = 0;
         carry_helper2[i] = 0;
      }

      for (i = 15; i >= 0; i--)
      {
         helper_2 = m[i];

         for(j = 15; j >= 0; j--)
         {
            helper_1 = m[j];

            if(carry_helper2[i+j+1] != 0)
            {
               if (m2[i+j+1] > MAX_VALUE_INT - carry_helper2[i+j+1])
               {
                  carry_helper2[i+j]++;
               }
               m2[i+j+1] += carry_helper2[i+j+1];
               carry_helper2[i+j+1] = 0;
            }


            temp = helper_1;
             temp *= helper_2;
             temp_1 = temp & 0x00000000ffffffff;
             if (m2[i+j+1] > MAX_VALUE_INT - temp_1)
             {
               carry_helper2[i+j]++;
             }
             m2[i+j+1] += temp_1;
             

             temp_1 = (temp & 0xffffffff00000000)>>32;
             if (m2[i+j] > MAX_VALUE_INT - temp_1)
             {
               carry_helper2[i+j-1]++;// this wont go to -ve values because 256 bits * 256 bits <= 512 bits
             }
             m2[i+j] += temp_1;
          
         }
      }

      m2[0] += carry_helper2[0];








for (i = 0; i < 32; i++)
{
   carry_helper2[i] = 0;
}

	
	helper_1 = s_2_x[3] & 0x00000000ffffffff;
	if (m2[31] > MAX_VALUE_INT - helper_1)
	{
		carry_helper2[31] = 1;
	}
	m2[31] += helper_1;
	for (i = 30; i >= 0; i--)
	{
		if (i < 24)
		{
			helper_1 = 0xffffffff;	// Assuming that +1 from 2's complement is absorbed by previous bits!!
		}
		else if(i%2 == 0)
		{
			helper_1 = (s_2_x[(i-24)/2] & 0xffffffff00000000)>>32;
		}
		else
		{
			helper_1 = s_2_x[(i-24)/2] & 0x00000000ffffffff;
		}

		if (m2[i] < MAX_VALUE_INT - helper_1)
	 	{
		    m2[i] += helper_1 + carry_helper2[i+1];
	 	}
	 	else if (m2[i] > MAX_VALUE_INT - helper_1)
	 	{
		    carry_helper2[i] = 1; 
		    m2[i] += helper_1 + carry_helper2[i+1];  // This temp_overflow is not gonna cause another overflow (f+f=1e which is 1 less than 1f)
	 	}
	 	else
	 	{
		    if(carry_helper2[i+1] == 1)
		    {
		       carry_helper2[i] = 1;
		       m2[i] = 0;
		    }
		    else
		    {
		       m2[i] = 0xffffffff;
		    }
	 	}
	}


// I am assuming that m2 is greater than s_x
// if(carry_helper2[0] != 1)
// {
// 	printf("m2<s_x Problem!!\n\n\n\n");
// }
	// The below code is if m2 < s_x
if(carry_helper2[0] == 0)
{
		for (i = 1; i < 9; i++)
		{
		   carry_helper2[i] = 0;
		}


		
		for (i = 7; i >= 0; i--)
		{
			if (p_max[i] < MAX_VALUE_INT - m2[i])
		 	{
			    m2[i] += p_max[i] + carry_helper2[i+1];
		 	}
		 	else if (p_max[i] > MAX_VALUE_INT - m2[i])
		 	{
			    carry_helper2[i] = 1; 
			    m2[i] += p_max[i] + carry_helper2[i+1];  // This carry_helper2 is not gonna cause another overflow (f+f=1e which is 1 less than 1f)
		 	}
		 	else
		 	{
			    if(carry_helper2[i+1] == 1)
			    {
			       carry_helper2[i] = 1;
			       m2[i] = 0;
			    }
			    else
			    {
			       m2[i] = 0xffffffff;
			    }
		 	}
		}
}









for (i = 0; i < 32; i++)
{
   carry_helper2[i] = 0;
}

point_x[0] = ~point_x[0]; point_x[1] = ~point_x[1]; point_x[2] = ~point_x[2]; point_x[3] = ~point_x[3];
// dont forget to add 1 courtesy of 2's complement
for (i = 3; i >= 0; i--)
{	
	if (point_x[i] == 0xffffffffffffffff)
	{
		point_x[i] = 0;
		continue;
	}
	point_x[i] += 1;
	break;
}
//point_x < p and you can add 1 to p without overflow at MSB


helper_1 = point_x[3] & 0x00000000ffffffff;
	if (m2[31] > MAX_VALUE_INT - helper_1)
	{
		carry_helper2[31] = 1;
	}
	m2[31] += helper_1;
	for (i = 30; i >= 0; i--)
	{
		if (i < 24)
		{
			helper_1 = 0xffffffff;// point_x cannot be 0 and is < p, so adding 1 wont cause overflow after at (or after.. whatever) msb
		}
		else if(i%2 == 0)
		{
			helper_1 = (point_x[(i-24)/2] & 0xffffffff00000000)>>32;
		}
		else
		{
			helper_1 = point_x[(i-24)/2] & 0x00000000ffffffff;
		}

		if (m2[i] < MAX_VALUE_INT - helper_1)
	 	{
		    m2[i] += helper_1 + carry_helper2[i+1];
	 	}
	 	else if (m2[i] > MAX_VALUE_INT - helper_1)
	 	{
		    carry_helper2[i] = 1; 
		    m2[i] += helper_1 + carry_helper2[i+1];  // This temp_overflow is not gonna cause another overflow (f+f=1e which is 1 less than 1f)
	 	}
	 	else
	 	{
		    if(carry_helper2[i+1] == 1)
		    {
		       carry_helper2[i] = 1;
		       m2[i] = 0;
		    }
		    else
		    {
		       m2[i] = 0xffffffff;
		    }
	 	}
	}




// I am assuming that m2-s_x is greater than point_x
// if(carry_helper2[0] != 1)
// {
// 	printf("m2-s_x<point_x Problem!!\n\n\n\n");
// }
	// Below code is the remedy for above!!

if(carry_helper2[0] == 0)
{
		for (i = 1; i < 9; i++)
		{
		   carry_helper2[i] = 0;
		}


		
		for (i = 7; i >= 0; i--)
		{
			if (p_max[i] < MAX_VALUE_INT - m2[i])
		 	{
			    m2[i] += p_max[i] + carry_helper2[i+1];
		 	}
		 	else if (p_max[i] > MAX_VALUE_INT - m2[i])
		 	{
			    carry_helper2[i] = 1; 
			    m2[i] += p_max[i] + carry_helper2[i+1];  // This carry_helper2 is not gonna cause another overflow (f+f=1e which is 1 less than 1f)
		 	}
		 	else
		 	{
			    if(carry_helper2[i+1] == 1)
			    {
			       carry_helper2[i] = 1;
			       m2[i] = 0;
			    }
			    else
			    {
			       m2[i] = 0xffffffff;
			    }
		 	}
		}
}








// m2 % p and in long 16 char each format.. Or see how it's comfortable to have point_x in and give the first input accordingly
// Keep the answer in m2 only!!
// 32*32 bits - p with msb 1

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
            // It wont be equal!!



            




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





// End of Mod




for (i = 30; i >= 24; i -= 2)
{
	temp = m2[i];
	temp = temp<<32;
	point_x[(i-24)/2] = temp + m2[i+1];
}


