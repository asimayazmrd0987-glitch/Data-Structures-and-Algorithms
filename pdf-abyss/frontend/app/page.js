import { safeGet } from "../lib/api";

export const runtime = "edge";
export const dynamic = "force-dynamic";

export default async function Home({ searchParams }) {
  const sp = (await searchParams) || {};
  const category = typeof sp.category === "string" ? sp.category : "";
  const q = typeof sp.q === "string" ? sp.q : "";

  const params = new URLSearchParams({ limit: "30" });
  if (category) params.set("category", category);
  if (q) params.set("q", q);

  const [cats, filesRes] = await Promise.all([
    safeGet("/categories"),
    safeGet(`/files?${params.toString()}`),
  ]);

  const categories = cats.data || [];
  const files = filesRes.data || [];
  const apiDown = !!(cats.error && filesRes.error);

  return (
    <div>
      <section className="hero">
        <h1>Find &amp; share <em>PDFs</em> without limits.</h1>
        <p>Books, past papers, lecture notes and research. Every upload is scanned for malware before it is published.</p>
        <form className="search" action="/" method="get">
          <input name="q" defaultValue={q} placeholder="Search by title or description..." />
          {category && <input type="hidden" name="category" value={category} />}
          <button className="btn" type="submit">Search</button>
        </form>
      </section>

      {apiDown && (
        <div className="banner">
          The website is running, but it cannot reach its API server yet. Set
          <b> NEXT_PUBLIC_API_URL </b> to your deployed backend and redeploy (see README).
        </div>
      )}

      {categories.length > 0 && (
        <>
          <h2>Subjects</h2>
          <div className="chips">
            <a className={`chip ${!category ? "active" : ""}`} href="/">All</a>
            {categories.map((c) => (
              <a key={c.id} className={`chip ${category === c.slug ? "active" : ""}`} href={`/?category=${encodeURIComponent(c.slug)}`}>
                {c.name}
              </a>
            ))}
          </div>
        </>
      )}

      <h2>{q || category ? "Results" : "Latest published PDFs"}</h2>
      {files.length === 0 ? (
        <div className="empty">
          {apiDown ? "No data to show while the API is offline." : "No published PDFs yet. "}
          {!apiDown && <a href="/upload">Upload the first one</a>}
        </div>
      ) : (
        <div className="grid">
          {files.map((f) => (
            <a key={f.id} className="card" href={`/files/${f.id}`}>
              <h3>{f.title}</h3>
              <div className="meta">
                <span className="badge">{f.category?.name || "Uncategorized"}</span>
                {f.document_type && <span className="badge">{f.document_type}</span>}
              </div>
            </a>
          ))}
        </div>
      )}
    </div>
  );
}
