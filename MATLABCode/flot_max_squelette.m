function [ F, flot, X, Xb ] = flot_max_squelette( G , source, puits, flot)
%
% Calcul du flot maximum dans le graphe G entre les noeuds source et puits
%
% G est d�crit par une structure matlab :
% G.n : nb de noeuds
% G.succ : cells de taille G.n, chaque "cell" i est un tableau de taille 
%          le nb de successeurs de i, donnant les num�ros des successeurs
% G.c    : capacit� (m�me structure que G.succ)
% G.pred : idem que G.succ mais avec les pr�d�cesseurs
%
% F : valeur du flot obtenu
% flot : description du flot par ar�te (m�me structure que G.c)
% X, Xb : coupe minimale associ�e au flot maximum


% initialisations 
if nargin <= 3   % un flot initial n'est pas fourni => init par flot nul
    flot = G.c;
    for i = 1:numel(flot)  % on met le flot de chaque arete à 0
        flot{i} = zeros(size(flot{i}));
    end
    F = 0;
else
    F = sum(flot{source});
end

% tableaux annexes : au max on aura n noeuds dans une chaine ameliorante
chn = zeros(1,G.n);
orig = zeros(1,G.n); 
ec = zeros(1,G.n);   

while 1    % répéter...

    % initialisations
    succes = 0;
    head = 1; queue = 1;
    chn(1) = source; orig(1) = nan; ec(1) = inf;
    marque = zeros(1,G.n); marque(source) = 1;  % initialisation marquage    

    while ~succes && queue - head >= 0   % construction de la chaine (file largeur)

        nc = chn(head);

        % on met dans la file tous les successeurs possibles
        for i = 1:numel(G.succ{nc})
            nn = G.succ{nc}(i);  % noeud à tester
            if marque(nn) == 0
                if flot{nc}(i) < G.c{nc}(i)    
                    marque(nn) = 1;
                    chn(queue+1)=nn;
                    queue = queue+1;
                    orig(queue) = nc;
                    ec(queue) = min(ec(head),G.c{nc}(i)-flot{nc}(i));
                    if nn == puits    % priorité au puits...
                        succes = 1; break;
                    end 
                end
            end
            
            % lorsqu'un noeud nn est inséré penser à tester s'il est le puits :
        end
        
        if ~succes % on regarde parmi les prédécesseurs

           % on met dans la file tous les prédecesseurs possibles
           for i = 1:numel(G.pred{nc})
               nn = G.pred{nc}(i);
               for j = 1:numel(G.succ(nn))
                   if G.succ{nn}(j) == nc
                       k = j;
                   end
               end
               
                if marque(nn) == 0
                    if flot{nn}(k) > 0    
                        marque(nn) = 1;
                        chn(queue+1)=nn;
                        queue = queue+1;
                        orig(queue) = -1*nc;
                        ec(queue) = min(ec(head),flot{nn}(k));
                    end
                end
           end
        end

        % mise à jour de la tete
        head = head + 1;
    end

    % affichage chaine
    affiche_chaine(chn, orig, ec, queue)

    if succes 
       [F, flot] = maj_flot(F, flot, G, chn, orig, ec, source, queue);
    else        % plus de chaine améliorante => on sort 
       break
    end

end
    
% coupe minimale.
X = find(marque); Xb = find(~marque);

    
