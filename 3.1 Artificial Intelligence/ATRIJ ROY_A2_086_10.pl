/* ==============================
   MOVIE DATABASE
   ============================== */

% --- Facts ---
movie(anna, 1987).
director(anna, yurek_bogayevicz).
actress(anna, sally_kirkland, anna).
actor(anna, robert_fields, daniel).
actress(anna, paulina_porizkova, krystyna).

movie(barton_fink, 1991).
director(barton_fink, ethan_coen).
director(barton_fink, joel_coen).
actor(barton_fink, martin_azarow, barton_fink).
actor(barton_fink, john_goodman, charlie_meadows).
actor(barton_fink, harry_bugin, pete).

movie(the_big_lebowski, 1998).
director(the_big_lebowski, joel_coen).
actor(the_big_lebowski, jeff_bridges, jeffrey_lebowski__the_dude).
actor(the_big_lebowski, john_goodman, walter_sobchak).
actor(the_big_lebowski, jack_kehler, marty).
actor(the_big_lebowski, harry_bugin, arthur_digby_sellers).
actor(the_big_lebowski, jesse_flanagan, little_larry_sellers).
actress(the_big_lebowski, irene_olga_l_pez, pilar_sellers_housekeeper).
actor(the_big_lebowski, luis_colina, corvette_owner).
actor(the_big_lebowski, ben_gazzara, jackie_treehorn).
actor(the_big_lebowski, leon_russom, malibu_police_chief).
actress(the_big_lebowski, robin_jones, checker_at_ralph_s).

movie(blade_runner, 1997).
director(blade_runner, joseph_d_kucan).
actor(blade_runner, martin_azarow, dino_klein).
actor(blade_runner, lloyd_bell, additional_voices).
actor(blade_runner, mark_benninghoffen, ray_mccoy).
actress(blade_runner, robin_jones, runciter).
actress(blade_runner, gwen_castaldi, dispatcher_and_newscaster).
actress(blade_runner, signy_coleman, dektora).

movie(blood_simple, 1984).
director(blood_simple, ethan_coen).
director(blood_simple, joel_coen).
actor(blood_simple, john_getz, ray).
actress(blood_simple, frances_mcdormand, abby).
actress(blood_simple, raquel_gavia, landlady).

/* ==============================
   RULES (Question #1)
   ============================== */

% a. Movie released after a given year
released_after(M, Y) :-
    movie(M, Y1),
    Y1 > Y.

% b. Movie released before a given year
released_before(M, Y) :-
    movie(M, Y1),
    Y1 < Y.

% c. Movies released in the same year
same_year(M1, M2) :-
    movie(M1, Y),
    movie(M2, Y),
    M1 \= M2.

% d. Two actors/actresses are co-stars if they appear in the same movie
co_star(A1, A2) :-
    (
        actor(M, A1, _);
        actress(M, A1, _)
    ),
    (
        actor(M, A2, _);
        actress(M, A2, _)
    ),
    A1 \= A2.