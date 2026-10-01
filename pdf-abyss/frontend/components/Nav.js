"use client";

import { useEffect, useState } from "react";

export default function Nav() {
  const [loggedIn, setLoggedIn] = useState(false);

  useEffect(() => {
    try {
      setLoggedIn(!!localStorage.getItem("token"));
    } catch {}
  }, []);

  function logout() {
    try {
      localStorage.removeItem("token");
    } catch {}
    window.location.href = "/";
  }

  return (
    <nav className="nav">
      <a href="/">Browse</a>
      <a href="/upload">Upload</a>
      {loggedIn ? (
        <button onClick={logout}>Logout</button>
      ) : (
        <>
          <a href="/login">Login</a>
          <a href="/register" className="cta">Register</a>
        </>
      )}
    </nav>
  );
}
