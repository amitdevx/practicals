// Async/Await User Login Simulation
const authenticateUser = async (username, password) => {
    return new Promise((resolve, reject) => {
        setTimeout(() => {
            if (username === "admin" && password === "secret123") {
                resolve("Login Successful! Welcome to the dashboard.");
            } else {
                reject(new Error("Invalid Username or Password!"));
            }
        }, 300);
    });
};

const handleLogin = async (user, pass) => {
    try {
        console.log(`Attempting login for '${user}'...`);
        const message = await authenticateUser(user, pass);
        console.log(`[+] Success: ${message}`);
    } catch (error) {
        console.error(`[-] Error: ${error.message}`);
    }
};

(async () => {
    await handleLogin("admin", "secret123");
    await handleLogin("guest", "wrongpass");
})();
