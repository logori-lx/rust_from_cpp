use std::io;
use std::cmp::Ordering;
use rand::Rng;
fn main(){
    println!("This is a guessing game!");
    let secret_number = rand::thread_rng().gen_range(1..=100);
    println!("The secret number is: {secret_number}");
    let mut guess = String::new();
    loop{
        guess.clear();
        println!("Please input your guess:");
        io::stdin().
            read_line(& mut guess).
            expect("Failed to read bytes!");
        println!("You guessed: {guess}");
        let guess : u32 = match guess.trim().parse() {
            Ok(num) => num,
            Err(_) => continue,
        };
        match guess.cmp(&secret_number){
            Ordering::Less => println!("Too Small"),
            Ordering::Equal => {
                println!("Equal");
                break;
            },
            Ordering::Greater => println!("Too large"),
        }
    }
    

    
}