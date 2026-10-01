"use client";

import { useState } from "react";
import { API_URL } from "../../lib/api";

export default function LoginPage() {
  const [email, setEmail] = useState("");
  const [password, setPassword] = useState("");
  const [message, setMessage] = useState("");
  const [busy, setBusy] = useState(false);

  async function submit(e) {
    e.preventDefault();
    setMessage("");
    setBusy(true);
    try {
      const res = await fetch(`${API_URL}/auth/login`, {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ email, password }),
      });
      if (!res.ok) {
        setMessage(res.status === 401 ? "Wrong email or password." : `Login failed (${res.status}).`);
        return;
      }
      const data = await res.json();
      localStorage.setItem("token", data.access_token);
      window.location.href = "/upload";
    } catch {
      setMessage("Cannot reach the server. Check NEXT_PUBLIC_API_URL and that the backend is running.");
    } finally {
      setBusy(false);
    }
  }

  return (
    <div className="panel form">
      <h1>Login</h1>
      <p className="sub">Welcome back. Log in to upload PDFs.</p>
      <form onSubmit={submit} className="form">
        <input placeholder="Email" type="email" value={email} onChange={(e) => setEmail(e.target.value)} required />
        <input placeholder="Password" type="password" value={password} onChange={(e) => setPassword(e.target.value)} required />
        <button className="btn" type="submit" disabled={busy}>{busy ? "Logging in..." : "Login"}</button>
      </form>
      {message && <div className="msg err">{message}</div>}
      <p className="sub">No account? <a href="/register">Register</a></p>
    </div>
  );
}
