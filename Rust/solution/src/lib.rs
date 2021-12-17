
pub struct NucleotideCounter {
    pub a: usize,
    pub c: usize,
    pub g: usize,
    pub t: usize,
}

pub fn counts(dna: &[char]) -> NucleotideCounter {

    let mut counter = NucleotideCounter {
        a: 0,
        c: 0,
        g: 0,
        t: 0
    };

    for base in dna {
        match base {
            'A' => counter.a += 1,
            'C' => counter.c += 1,
            'G' => counter.g += 1,
            'T' => counter.t += 1,
            _   => panic!("What the f@ck")
        }
    }

    counter
}

pub fn dna_complement(dna: &[char]) -> Vec<char> {
    let mut complements = Vec::new();

    for base in dna {
        match base {
            'A' => complements.push('T'),
            'T' => complements.push('A'),
            'G' => complements.push('C'),
            'C' => complements.push('G'),
             _  => panic!("What the f@ck")
        }
    }

    complements
}

pub fn reverse_rna_complement(dna: &[char]) -> Vec<char> {
    let mut complements = Vec::new();

    for base in dna.iter().rev() {
        match base {
            'A' => complements.push('U'),
            'T' => complements.push('A'),
            'G' => complements.push('C'),
            'C' => complements.push('G'),
             _  => panic!("What the f@ck")
        }
    }

    complements
}

