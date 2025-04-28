using dz10.Model;
using Microsoft.EntityFrameworkCore;
using WebApplication2.Repositories;

namespace dz10.Repository
{
    public class CommentRepository : ICommentRepository
    {
        private readonly AppDbContext _db;

        public CommentRepository(AppDbContext db)
        {
            _db = db;
            _db.Database.EnsureCreated();
        }

        public IEnumerable<Comment> GetAll() => _db.Comments.ToList();

        public Comment? GetById(int id) => _db.Comments.Find(id);

        public Comment Add(Comment comment)
        {
            _db.Comments.Add(comment);
            _db.SaveChanges();
            return comment;
        }

        public Comment? Update(int id, Comment comment)
        {
            var existingComment = _db.Comments.Find(id);
            if (existingComment == null) return null;

            existingComment.Name = comment.Name ?? existingComment.Name;
            existingComment.Email = comment.Email ?? existingComment.Email;
            existingComment.Body = comment.Body ?? existingComment.Body;
            existingComment.PostId = comment.PostId != 0 ? comment.PostId : existingComment.PostId;

            _db.SaveChanges();
            return existingComment;
        }

        public bool Delete(int id)
        {
            var comment = _db.Comments.Find(id);
            if (comment == null) return false;

            _db.Comments.Remove(comment);
            _db.SaveChanges();
            return true;
        }
    }
}