#!/usr/bin/env zsh
tests=(./*.test)

if [ ${#tests[@]} -eq 0 ]; then
    echo "Aucun fichier .test trouvé dans le répertoire courant."
    exit 0
fi

failed=0

for t in "${tests[@]}"; do
    printf "== Exécution : %s ==\n" "$t"
    if ../bin/cpyrrc < "$t"; then
        printf "-- OK : %s --\n\n" "$t"
    else
        printf "** ECHEC : %s **\n\n" "$t"
        failed=1
    fi
done

exit $failed