(* Problem 4.6 *)

Section DeMorgan.
  Variables x y : nat.
  Variables A B : Prop.
  
  Hypothesis Stab: forall (A : Prop), ~~A -> A.
  
  Lemma Not_A_and_B_implies_notA_or_notB : ~(A /\ B) -> ~A \/ ~B.
    intro.
    apply Stab.
    intro.
    apply H.
    split.
    apply Stab.
    intro.
    apply H0.
    left.
    apply H1.
    apply Stab.
    intro.
    apply H0.
    right.
    apply H1.
  Qed.
  
  Lemma NotA_or_notB_implies_Not_A_and_B: (~A \/ ~B) -> ~(A /\ B).
    intro.
    elim H.
    intro.
    intro.
    apply H0.
    apply H1.
    intro.
    intro.
    apply H0.
    apply H1.
  Qed.
  Lemma Not_A_or_B_implies_notA_and_notB: ~(A \/ B) -> ~A /\ ~B.
    intro.
    split.
    intro.
    apply H.
    left.
    apply H0.
    intro.
    apply H.
    right.
    apply H0.
  Qed.
  
  Lemma NotA_and_notB_implies_not_A_or_B: ~A /\ ~B -> ~(A \/ B).
    intro.
    intro.
    elim H.
    intro.
    intro.
    elim H0.
    apply H1.
    apply H2.
  Qed.
    
  Variables p : nat -> Prop.
  
  Lemma Not_All_x_A_implies_exists_x_not_A: ~(forall x, p x) -> exists x , ~ p x.
    apply Stab.
    intro.
    apply H.
    intro.
    exists y.
    intro.
    apply H0.
    intro X.
    apply Stab.
    intro.
    apply H.
    intro.
    exists X.
    apply H2.
  Qed.
  
  Lemma Exists_x_not_A_implies_not_all_x_A: (exists x, ~ p x) -> ~(forall x, p x).
    intro.
    intro.
    elim H.
    intro.
    intro.
    apply H1.
    apply H0.
  Qed.
  
  Lemma Not_exists_x_A_implies_all_x_not_A: ~(exists x, p x) -> (forall x, ~ p x).
    intro.
    intro X.
    intro.
    apply H.
    exists X.
    apply H0.
  Qed.
End DeMorgan.
