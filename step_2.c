m1[0] = 0;
    m1[1] = 0;
    m1[2] = 0;
    m1[3] = 1;
    recursion = 256;


    // while((once == 0 and recursion != 0) or (once == 1))
    while(recursion != 0)
    {





        // Calculating m1*m1
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
                    helper_1 = m1[j/2] & 0x00000000ffffffff;
                }
                else
                {
                    helper_1 = (m1[j/2] & 0xffffffff00000000)>>32;
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

        // End m1*m1
        // Now find mod

        for (i = 0; i < 16; i++)
        {
            mod_helper_2[i] = 0;
        }

        for (i = 0; i < 257; i++)
        {
            if(i%32 == 0)
            {
                if (i/32 != 0)
                    {
                        mod_helper_2[(i/32) - 1] = 0;
                    }
                    for (j = 0; j < 8; j++)
                    {
                        mod_helper_2[i/32 + j] = p_mod[32*9 - 1 - 8 + j];
                    }

            }
            else
            {
                for (j = 0; j < 9; j++)
                {
                    mod_helper_2[i/32 + j] = p_mod[(32-(i%32))*9 - 1 - 8 + j];
                }

            }
            // Now check if m is greater than mod_helper_2. If yes, subtract mod_helper_2 from m
            greater = 0;
            for (j = 0; j < 16; j++)
            {
                if (m[j] > mod_helper_2[j])
                {
                    greater = 1;
                    break;
                }
                if (m[j] < mod_helper_2[j])
                {
                    break;
                }
            }

            if(greater == 1)
            {
                for (j = 0; j < 16; j++)
                {
                    mod_helper_3[j] = ~(mod_helper_2[j]);
                }

                for (j = 15; j >= 0; j--)
                {
                    if (mod_helper_3[j] == 0xffffffff)
                    {
                        mod_helper_3[j] = 0;
                        continue;
                    }
                    mod_helper_3[j] += 1;
                    break;
                }

               for (j = 0; j < 16; j++)
               {
                    carry_helper[j] = 0;
               }

                // add m and mod_helper_3

               if (m[15] > MAX_VALUE_INT - mod_helper_3[15])
               {
                  carry_helper[15] = 1;
               }
               m[15] += mod_helper_3[15];
               for (j = 14; j >= 0; j--)
               {
                  if (m[j] < MAX_VALUE_INT - mod_helper_3[j])
                  {
                      m[j] += mod_helper_3[j] + carry_helper[j+1];
                  }
                  else if (m[j] > MAX_VALUE_INT - mod_helper_3[j])
                  {
                      carry_helper[j] = 1;
                      m[j] += mod_helper_3[j] + carry_helper[j+1];
                  }
                  else
                  {
                      if(carry_helper[j+1] == 1)
                      {
                         carry_helper[j] = 1;
                         m[j] = 0;
                      }
                      else
                      {
                         m[j] = 0xffffffff;
                      }
                  }
               }


            }

        }

        for (i = 14; i >= 8; i -= 2)
        {
            temp = m[i];
            temp = temp<<32;
            m1[(i-8)/2] = temp + m[i+1];
        }


        recursion--;
        if ((recursion != 32) && (recursion != 9) && (recursion != 8) && (recursion != 7) && (recursion != 6) && (recursion != 4) && (recursion != 1))
        {
            // calculate m1 * k1 mod p and then dump the value in m1
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

            // Now find mod and dump in m1

            for (i = 0; i < 16; i++)
            {
                mod_helper_2[i] = 0;
            }

            for (i = 0; i < 257; i++)
            {
                if(i%32 == 0)
                {
                    if (i/32 != 0)
                    {
                        mod_helper_2[(i/32) - 1] = 0;
                    }
                    for (j = 0; j < 8; j++)
                    {
                        mod_helper_2[i/32 + j] = p_mod[32*9 - 1 - 8 + j];
                    }
                }
                else
                {
                    for (j = 0; j < 9; j++)
                    {
                        mod_helper_2[i/32 + j] = p_mod[(32-(i%32))*9 - 1 - 8 + j];
                    }

                }


                greater = 0;
                for (j = 0; j < 16; j++)
                {
                    if (m[j] > mod_helper_2[j])
                    {
                        greater = 1;
                        break;
                    }
                    if (m[j] < mod_helper_2[j])
                    {
                        break;
                    }
                }



                if (greater == 1)
                {
                    for (j = 0; j < 16; j++)
                    {
                        mod_helper_3[j] = ~(mod_helper_2[j]);
                    }

                   for (j = 15; j >= 0; j--)
                   {
                      if (mod_helper_3[j] == 0xffffffff)
                      {
                         mod_helper_3[j] = 0;
                         continue;
                      }
                      mod_helper_3[j] += 1;
                      break;
                   }

                   for (j = 0; j < 16; j++)
                   {
                      carry_helper[j] = 0;
                   }

                   // add m and mod_helper_3

                   if (m[15] > MAX_VALUE_INT - mod_helper_3[15])
                   {
                      carry_helper[15] = 1;
                   }
                   m[15] += mod_helper_3[15];
                   for (j = 14; j >= 0; j--)
                   {
                      if (m[j] < MAX_VALUE_INT - mod_helper_3[j])
                      {
                          m[j] += mod_helper_3[j] + carry_helper[j+1];
                      }
                      else if (m[j] > MAX_VALUE_INT - mod_helper_3[j])
                      {
                          carry_helper[j] = 1;
                          m[j] += mod_helper_3[j] + carry_helper[j+1];
                      }
                      else
                      {
                          if(carry_helper[j+1] == 1)
                          {
                             carry_helper[j] = 1;
                             m[j] = 0;
                          }
                          else
                          {
                             m[j] = 0xffffffff;
                          }
                      }
                   }

                }


           }

            for (i = 14; i >= 8; i -= 2)
            {
                temp = m[i];
                temp = temp<<32;
                m1[(i-8)/2] = temp + m[i+1];
            }






        }




    }
