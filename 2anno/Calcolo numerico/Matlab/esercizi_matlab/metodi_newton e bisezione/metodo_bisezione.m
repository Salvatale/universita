function[x,e,num_iter] = metodo_bisezione(tolleranza,a,b,f)
   errore = abs(b-a);
   num_iter= 1;
   while errore > tolleranza
       x = (a+b)/2;
       if (f(x)*f(a)) < 0
           b = x;
       elseif f(x) == 0
           return;
       else
           a = x;
       errore = abs(b-a);
       e(num_iter) = errore;
       num_iter = num_iter + 1;
       end
   end
end