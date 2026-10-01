export const API_URL = (process.env.NEXT_PUBLIC_API_URL || "http://localhost:8000").replace(/\/+$/, "");

// Never throws: returns { data, error } so pages always render.
export async function safeGet(path) {
  try {
    const res = await fetch(`${API_URL}${path}`, { cache: "no-store" });
    if (!res.ok) return { data: null, error: `API responded ${res.status}`, status: res.status };
    return { data: await res.json(), error: null, status: res.status };
  } catch (e) {
    return { data: null, error: "Cannot reach the API server", status: 0 };
  }
}
