# Computaci-n-Grafica
```c

inp_to_ndc(double , double)
{
  ndcx = dcx / ndh-1;
  ndcy = dcy / ndv-1;
  return  ndcx,ndcy; 
}

ndc_to_user(double , double)
{
  x= ndcx*100;
  y= ndcy*100;
  return x,y;
}

user_to_ndc(double , double)
{
  ndcx=x/100;
  ndcy=y/100;
  return ndcx,ndcy;
}

ndc_to_dc(double , double)
{
  dcx=round(ndcx*(ndh-1));
  dcy=round(ndcy*(ndv-1));
  return dcx,dcy;
}

```
