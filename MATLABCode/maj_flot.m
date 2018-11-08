function [F, flot] = maj_flot(F, flot, G, chn, orig, ec, source, queue)   
    % mise à jour du flot
    delta = ec(queue);
    F = F + delta;
    while 1
        nc = chn(queue);
        np = orig(queue);
        if np > 0
            k = find( nc == G.succ{np} );
            flot{np}(k) = flot{np}(k) + delta;
        else
            np = -np;
            k = find( np == G.succ{nc} );
            flot{nc}(k) = flot{nc}(k) - delta;
        end
        if np == source
            break
        else  % recherche du noeud précédent de la chaîne
            queue = queue-1;
            while chn(queue) ~= np, queue = queue-1; end
        end
    end           
end
