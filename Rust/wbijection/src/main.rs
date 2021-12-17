

fn calculate_natural_repr(word: &str) -> u128 {
    if word == "" {
        return 0;
    }

    if word.len() == 1 {
        return (word.as_bytes()[0] as u128) + 1;
    }

    let mut chars = word.chars();
    let last_char = chars.next_back();

    144_697 * calculate_natural_repr(chars.as_str()) + (last_char.unwrap() as u128)
}

fn word_bijection(word: &String) -> Result<u128, &str>   {
    let words: Vec<&str> = word.split(" ").collect();

    if words.len() > 1 {
        return Err("Only one word can be passed");
    }

    let word: &str = words[0];

    Ok(calculate_natural_repr(word))
}

fn main() {
    println!("Крак: {}", word_bijection(&String::from("Крак")).unwrap());
}
