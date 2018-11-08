function parcours_largeur(G,noeud_init)
   marque = zeros(1,G.n);                      % tableau pour marquage
   marque(noeud_init)=1;                       % on marque le noeud initial
   file = zeros(1,G.n);                        % tableau pour la file
   head = 1; queue = 1; file(1) = noeud_init;  % initialisation de la file
   fprintf('\n noeuds successifs visités : %d', noeud_init)
   while queue-head >= 0                       % tant que la file n'est pas vide
      % on prend le sommet en début de file
      headFile = file(head);                                        
      % on affiche et met en queue de file tous ses successeurs non marques 
      % pour afficher un nouveau noeud de numéro nn on utilisera fprintf(',%d',nn)
      i = length(G.succ{headFile});
      for t=1:i
          nn = G.succ{headFile}(t);
          if marque(nn) == 0
            fprintf(',%d',nn);
            marque(nn) = 1;
            file(queue+1) =nn;
            queue = queue+1;
          end
      end
      % maj de la tête
      head = head +1;
   end
   fprintf('\n')
